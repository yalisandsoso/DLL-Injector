/* ============================================================================
* Copyright (c) 2012, Sebastian Eschweiler <advanced(dot)malware<dot>analyst[at]gmail.com>
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the <organization> nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* =============================================================================
*/

#include "CommandLine.h"
#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void parseCommandLine(int argc, _TCHAR* argv[], string& executable, DWORD& pid, bool& pause, string& dll)
{

	po::options_description desc("Options are");
	desc.add_options()
		("help,h", "show this message")
		("run,r", po::value<string>(&executable), "starts supplied executable and injects the DLL before any other DLL is loaded or the entry point is reached")
		("pid,p", po::value<DWORD>(&pid), "injects DLL into a running process denoted by supplied PID")
		("suspend,s", po::bool_switch(&pause)->default_value(false), "pause process after DLL injection. Useful for debugging")
		("dll,d", po::value<string>(&dll)->required(), "DLL to be injected");

	po::variables_map vm;

	try
	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	}
	catch (exception& e)
	{
		cerr << "[error] " << e.what() << endl;
		cout << desc << endl;
		exit(1);
	}

	if (vm.count("run") + vm.count("pid") != 1)
	{
		cerr << "[error] supply *either* --run *or* --pid argument" << endl;
		cout << desc << endl;
		exit(1);
	}

}

