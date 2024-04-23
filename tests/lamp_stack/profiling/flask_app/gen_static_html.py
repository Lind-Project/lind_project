import argparse
import jinja2
import os
import string
import random

parser = argparse.ArgumentParser(
    description="Script to generate a static HTML file for nginx benchmarking"
)
parser.add_argument(
    "-s", "--size", dest="size", type=int, default=17, help="File size in Log_2(N) bytes"
)
parser.add_argument(
    "-o",
    "--out-file",
    dest="out_file",
    type=str,
    default="static.html",
    help="Destination of the generated HTML file",
)

dir_path = os.path.dirname(os.path.realpath(__file__))


def rand_generator(size=2 ** 17, chars=string.ascii_uppercase + string.digits):
    return "".join(random.choice(chars) for _ in range(size))


def generate(file_size):
    template_loader = jinja2.FileSystemLoader(searchpath=os.path.join(dir_path, "templates"))
    template_env = jinja2.Environment(loader=template_loader)
    template_file = "static.html"
    template = template_env.get_template(template_file)

    content = rand_generator(int(file_size))
    return template.render(content=content)


def save(file_name, content):
    with open(os.path.join(dir_path, file_name), "w") as f:
        f.write(content)


if __name__ == "__main__":
    args = parser.parse_args()
    print "Generating static HTML file of size 2^{} Bytes".format(args.size)
    generated_content = generate(file_size=2 ** args.size)
    save(file_name=args.out_file, content=generated_content)
