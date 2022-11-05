# Include weaved .lit files from doc/literate

# -----------------------------------------------------

from subprocess import run
import os
from os.path import dirname, realpath, join, relpath, isfile, basename, splitext, isabs
from html.parser import HTMLParser

def abspath(path, root=""):
    if not isabs(path):
        return realpath(join(root, path))
    else:
        return realpath(path)

class LitOutputParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.body_start = None
        self.body_end = None

    def handle_starttag(self, tag, attrs):
        if tag == 'body':
            self.body_start = self.getpos()
            
    def handle_endtag(self, tag):
        if tag == 'body':
            self.body_end = self.getpos()

    def get_body_content(self, html_content):
        lines = html_content.split('\n')
        sl, so = self.body_start
        el, eo = self.body_end
        body_content = "".join(
            [lines[sl][so:]] +
            lines[sl+1:el] +
            [lines[el][:eo]]
        )
        return body_content.strip()[:-len("</body>")]

def build_lit(source_file, build_dir, lit_executable='lit'):
    name = splitext(basename(source_file))[0]
    htmlfile = join(build_dir, name + ".html")

    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    run([lit_executable, source_file, "-odir", build_dir])

    with open(htmlfile, "rb") as f:
        html_content = f.read().decode("utf-8")

    parser = LitOutputParser()
    parser.feed(html_content)
    return parser.get_body_content(html_content)

# -----------------------------------------------------

from docutils import nodes
from docutils.nodes import Element
from docutils.parsers.rst import Directive, directives
from sphinx.writers.html import HTMLTranslator
from sphinx.util import logging
from sphinx.errors import ExtensionError, ConfigError
import shutil

logger = logging.getLogger(__name__)

class LiterateNode(Element):
    def __init__(self, filename=None):
        super().__init__(self)
        self.filename = filename

class LiterateDirective(Directive):

    required_arguments = 1
    optional_arguments = 0

    def run(self):
        node = LiterateNode(filename=self.arguments[0])
        return [node]

class LiterateHTMLTranslator(HTMLTranslator):
    def __init__(self, document):
        super().__init__(self, document)

    def visit_literate_node_html(self, node):    
        check_config(self.config)

        # Resolve source path
        source_file = None
        all_candidates = []
        for path in self.config.literate_source_paths:
            path = abspath(path, root=dirname(node.source))
            candidate = realpath(join(path, node.filename))
            all_candidates.append(candidate)
            if isfile(candidate):
                source_file = candidate
                break

        if source_file is None:
            raise ExtensionError(
                f"Could not find literate source '{node.filename}' (included in {node.source})\n" +
                "  searched paths:\n" +
                "\n".join(["   - " + c for c in all_candidates])
            )

        # Resolve build dir
        if self.config.literate_build_dir == "":
            build_dir = join(dirname(source_file), "build", node.filename[:-4])
        else:
            subdir = splitext(relpath(source_file, start=self.builder.app.srcdir))[0]
            build_dir = join(self.config.literate_build_dir, subdir)

        content = build_lit(
            source_file,
            build_dir,
            lit_executable=self.config.literate_executable,
        )

        self.body.append(self.starttag(node, 'div', **{'class': "literate"}))
        self.body.append(content)

    def depart_literate_node_html(self, node):
        self.body.append('</div>')

def check_config(config):
    lit = config.literate_executable
    if shutil.which(lit) is None:
        logger.critical(f"The Literate command was not found (command: '{lit}')")
        raise ConfigError()

def setup(app):
    app.add_directive("literate", LiterateDirective)
    app.add_node(LiterateNode, html=(
        LiterateHTMLTranslator.visit_literate_node_html,
        LiterateHTMLTranslator.depart_literate_node_html
    ))
    app.add_config_value("literate_executable", "lit", "html")
    app.add_config_value("literate_source_paths", ["."], "html")
    app.add_config_value("literate_build_dir", "", "html")

    return {
        'version': '0.1',
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }

