# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information
import subprocess, sys, os


def run_doxygen(folder):
    try:
        retcode = subprocess.call('cd %s; doxygen ./Doxyfile' % folder, shell=True)
        if retcode < 0:
            sys.stderr.write("doxygen terminated by signal {:d}".format(retcode))
    except OSError as e:
        sys.stderr.write("doxygen execution failed: {}".format(e))


def generate_doxygen_xml(app):
    read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

    if read_the_docs_build:
        run_doxygen('..')

generate_doxygen_xml(None)
#def setup(app):
#    app.connect('builder-inited', generate_doxygen_xml)

project = 'ChessEngine'
copyright = '2024, Matthew Brown'
author = 'Matthew Brown'
release = 'v0.0.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'breathe'
]

templates_path = ['_templates']
exclude_patterns = ['Doxyfile']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'

breathe_projects = {
    "ChessEngine": "../xml"
}

breathe_default_project = "ChessEngine"


html_static_path = ['_static']
html_extra_path = ['../xml']