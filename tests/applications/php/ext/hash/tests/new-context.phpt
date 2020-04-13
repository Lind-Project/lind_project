--TEST--
Hash: Attempt to instantiate a HashContext directly
--SKIPIF--
<?php if (!extension_loaded('hash')) echo 'skip';
--FILE--
<?php

try {
  new HashContext;
} catch (Error $e) {
  echo "Exception: {$e->getMessage()}\n";
}
--EXPECT--
Exception: Call to private HashContext::__construct() from invalid context
