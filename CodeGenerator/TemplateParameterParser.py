# Authors: Philipp Harzig, Christoph Lassner.
import re

class TemplateParameterParser(object):
    """Parses a template definition of a cpp class into an array of those template parameters"""

    def __init__(self, filename, line):
        self.Filename = filename
        self.LineNo = line

    def RetrieveTemplateParameters(self):
        templateParamsStr = None
        fp = open(self.Filename)
        for i, line in enumerate(fp):
            if i == self.LineNo - 2:
                templateParamsStr = line.strip()
                # It occasionally happens that the line number is
                # one too small.
                if templateParamsStr.startswith('template'):
                  break
            if i == self.LineNo - 1:
                templateParamsStr = line.strip()
                break
        fp.close()

        if not templateParamsStr.startswith('template'):
          return None, ''

        pattern = "\s*template\s*<(.*?)>\n|\s*"
        regex = re.compile(pattern)
        if regex.match(templateParamsStr):
            typenames = re.findall('(typename|class)\s+([a-zA-Z0-9_]+)', templateParamsStr)
            typenames = [t[1] for t in typenames]
            return typenames, templateParamsStr
        else:
            return None, ''