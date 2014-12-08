"""
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*  Copyright (C) 2004 by Daniel M. Gass                                     *
*                                                                           *
*  This program is free software; you can redistribute it and/or modify it  *
*  under the terms of version 2 of the GNU General Public License as        *
*  published by the Free Software Foundation.                               *
*                                                                           *
*  This program is distributed in the hope that it will be useful, but      *
*  WITHOUT ANY WARRANTY; without even the implied warranty of               *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General *
*  Public License for more details.                                         *
*                                                                           *
*  You should have received a copy of the GNU General Public License along  *
*  with this program; if not, write to the Free Software Foundation, Inc.,  *
*  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA                    *
*                                                                           *
*  This software is distributed as part of the testgen test framework.      *
*            https://sourceforge.net/projects/testgen/                      *
*                                                                           *
*  You may contact the author at <dan.gass at gmail.com>                    *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
"""

from testgen.command import Command as _Command
from testgen.build import Builder as _Builder
from testgen.utils import FileFinder as _FileFinder
import os as _os

class IntegrationTestLinker(_Command):
    
    def run(self,files=[],flags='',input=None):
        return _Command.run(self, 
            files + ['-L"D:\Code\jv_json\source"', '-ljv_json'],
            flags, input)

KEYS = 'gnu'

# Config module always executes config scripts with the current directory
# set to where script is located.  Use this to determine where example
# source is stored.
_esp = _os.path.join(_os.getcwd(),'source')

# Settings for GNU tools

compiler = {'gnu' : _Command(cmd='g++ -c -I"%s"'%_esp)}
linker =   {'gnu' : IntegrationTestLinker(cmd=r'g++ -o unitTest.exe')}
builder =  {'gnu' : _Builder(objext='o')}
runner =   {'gnu' : _Command(cmd=r'.\unitTest.exe')}

# Settings for Microsoft tools

compiler['microsoft'] = {
    'c'   : _Command(cmd='cl.exe /nologo /W3 /c -I"%s"'%_esp,flags='/Tc'),
    'cpp' : _Command(cmd='cl.exe /nologo /W3 /c -I"%s"'%_esp,flags='/Tp')}
linker['microsoft'] = _Command(cmd='link.exe /OUT:unitTest.exe')
builder['microsoft'] = _Builder(objext='obj')
runner['microsoft'] = _Command(cmd='unitTest.exe')

# Set up a file finder that will search the current directory first and
# then look for source files in the example/source directory.  This 
# configuration setting is utilized by the C/C++ source file stubber.
file_finder = _FileFinder(['.',_esp])
