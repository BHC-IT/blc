/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include "blc/nonCopyable.hpp"
#include "blc/serializable.hpp"
#include "blc/errorHandle.hpp"
#include "blc/socket.hpp"
#include "blc/server.hpp"
#include "blc/client2way.hpp"
#include "blc/client.hpp"
#include "blc/singleServer.hpp"
#include "blc/protocolCaps.hpp"
#include "blc/protocolFactory.hpp"
#include "blc/pipe.hpp"
#include "blc/server2way.hpp"
#include "blc/stream.hpp"
#include "blc/pair.hpp"
#include "blc/blcmain.hpp"
#include "blc/cinReadable.hpp"
#include "blc/global.hpp"
#include "blc/actor.hpp"
#include "blc/bindTest.hpp"
#include "blc/regex.hpp"
#include "blc/float.hpp"
#include "blc/fileSize.hpp"
#include "blc/stringOp.hpp"
#include "blc/constraint.hpp"
#include "blc/concept.hpp"
#include "blc/promise.hpp"
#include "blc/VFiles.hpp"

#include "concept/operable.hpp"

namespace blc {
	/// contain basic tools.
	namespace tools {}

	/// contain error managment class.
	namespace error {}

	/// contain networking class.
	namespace network {}

	/// contain mathematical class.
	namespace math {}

	/// contain symbolique class.
	namespace symbole {}

	/// contain all the tools to build and use constraint and concept
	namespace concept {}
}  // namespace blc
