# Test some logical replication DDL behavior
use strict;
use warnings;
use PostgresNode;
use TestLib;
use Test::More tests => 1;

sub wait_for_caught_up
{
	my ($node, $appname) = @_;

	$node->poll_query_until('postgres',
"SELECT pg_current_wal_lsn() <= replay_lsn FROM pg_stat_replication WHERE application_name = '$appname';"
	) or die "Timed out while waiting for subscriber to catch up";
}

my $node_publisher = get_new_node('publisher');
$node_publisher->init(allows_streaming => 'logical');
$node_publisher->start;

my $node_subscriber = get_new_node('subscriber');
$node_subscriber->init(allows_streaming => 'logical');
$node_subscriber->start;

my $ddl = "CREATE TABLE test1 (a int, b text);";
$node_publisher->safe_psql('postgres', $ddl);
$node_subscriber->safe_psql('postgres', $ddl);

my $publisher_connstr = $node_publisher->connstr . ' dbname=postgres';
my $appname           = 'replication_test';

$node_publisher->safe_psql('postgres',
	"CREATE PUBLICATION mypub FOR ALL TABLES;");
$node_subscriber->safe_psql('postgres',
"CREATE SUBSCRIPTION mysub CONNECTION '$publisher_connstr application_name=$appname' PUBLICATION mypub;"
);

wait_for_caught_up($node_publisher, $appname);

$node_subscriber->safe_psql('postgres', q{
BEGIN;
ALTER SUBSCRIPTION mysub DISABLE;
ALTER SUBSCRIPTION mysub SET (slot_name = NONE);
DROP SUBSCRIPTION mysub;
COMMIT;
});

pass "subscription disable and drop in same transaction did not hang";

$node_subscriber->stop;
$node_publisher->stop;
