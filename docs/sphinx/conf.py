# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information
import subprocess, sys, os, os.path


def run_doxygen(folder):
    try:
        print("Moving to %s" % os.path.abspath(folder))
        os.chdir(folder)
        print("Running doxygen")
        retcode = subprocess.call('doxygen', shell=True)
        if retcode < 0:
            sys.stderr.write("doxygen terminated by signal {:d}".format(retcode))
        print(os.listdir())
        os.chdir('..')
        print("Returned")

    except OSError as e:
        sys.stderr.write("doxygen execution failed: {}".format(e))


def generate_doxygen_xml(app):
    read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

    if read_the_docs_build:
        os.makedirs('build', exist_ok=True)
        run_doxygen('..')

def setup(app):
    app.connect('builder-inited', generate_doxygen_xml)

html_extra_path = ['../build/xml']

project = 'ChessEngine'
copyright = '2024, Matthew Brown'
author = 'Matthew Brown'
release = 'v0.0.1'


extensions = [
    'breathe'
]

templates_path = ['_templates']

html_theme = 'alabaster'

breathe_projects = {
    "ChessEngine": "../build/xml"
}

breathe_default_project = "ChessEngine"

