#
# Internal file for GetGitRevisionDescription.cmake
#
# Requires CMake 2.6 or newer (uses the 'function' command)
#
# Original Author:
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright Iowa State University 2009-2010.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

set(HEAD_HASH)
set(GIT_D)

file(READ "D:/ogs/bb/CMakeFiles/git-data/HEAD" HEAD_CONTENTS LIMIT 1024)

string(STRIP "${HEAD_CONTENTS}" HEAD_CONTENTS)
if(HEAD_CONTENTS MATCHES "ref")
	# named branch
	string(REPLACE "ref: " "" HEAD_REF "${HEAD_CONTENTS}")

	set(GIT_D "D:/ogs/.git")
	# to make secondary git working directory work
	if(EXISTS "${GIT_D}/commondir")
		file(READ "${GIT_D}/commondir" cdir_contents LIMIT 1024)
		string(STRIP "${cdir_contents}" cdir_contents)
		set(GIT_D "${GIT_D}/${cdir_contents}")
	endif()

	if(EXISTS "${GIT_D}/${HEAD_REF}")
		configure_file("${GIT_D}/${HEAD_REF}" "D:/ogs/bb/CMakeFiles/git-data/head-ref" COPYONLY)
	elseif(EXISTS "${GIT_D}/logs/${HEAD_REF}")
		configure_file("${GIT_D}/logs/${HEAD_REF}" "D:/ogs/bb/CMakeFiles/git-data/head-ref" COPYONLY)
		set(HEAD_HASH "${HEAD_REF}")
	endif()
else()
	# detached HEAD
	configure_file("D:/ogs/.git/HEAD" "D:/ogs/bb/CMakeFiles/git-data/head-ref" COPYONLY)
endif()

if(NOT HEAD_HASH)
	file(READ "D:/ogs/bb/CMakeFiles/git-data/head-ref" HEAD_HASH LIMIT 1024)
	string(STRIP "${HEAD_HASH}" HEAD_HASH)
endif()
