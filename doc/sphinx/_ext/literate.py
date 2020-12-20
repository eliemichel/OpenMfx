# Include weaved .lit files from doc/literate

# -----------------------------------------------------

from subprocess import run
import os
from os.path import dirname, realpath, join

def build_lit(litfile, lit_source_dir):
    lit_source_dir = realpath(lit_source_dir)
    build_dir = join(lit_source_dir, "build")
    htmlfile = join(build_dir, litfile[:-4] + ".html")

    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    run(["lit", join(lit_source_dir, litfile), "-odir", build_dir])

    with open(htmlfile, "rb") as f:
        html_content = f.read().decode("utf-8")

    main_content = ""
    rec = False
    for line in html_content.split("\n"):
        if "<body" in line:
            rec = True
        if rec:
            if "</body>" in line:
                rec = False
            main_content += line

    return main_content

# -----------------------------------------------------

from docutils import nodes
from docutils.nodes import Element
from docutils.parsers.rst import Directive, directives
from sphinx.writers.html import HTMLTranslator

class literate_node(Element):
    def __init__(self, filename=None):
        super().__init__(self)
        self.filename = filename

class Literate(Directive):

    required_arguments = 1
    optional_arguments = 0

    def run(self):
        node = literate_node(filename=self.arguments[0])
        return [node]

class LiterateHTMLTranslator(HTMLTranslator):
    def __init__(self, document):
        HTMLTranslator.__init__(self, document)

    def visit_literate_node_html(self, node):
        lit_source_dir = join(self.builder.app.srcdir, self.config.literate_source_path)
        self.body.append(self.starttag(node, 'div', **{'class': "literate"}))
        self.body.append(build_lit(node.filename, lit_source_dir))

    def depart_literate_node_html(self, node):
        self.body.append('</div>')


def setup(app):
    app.add_directive("literate", Literate)
    app.add_node(literate_node, html=(
        LiterateHTMLTranslator.visit_literate_node_html,
        LiterateHTMLTranslator.depart_literate_node_html
    ))
    app.add_config_value("literate_source_path", ".", "html")

    return {
        'version': '0.1',
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }

