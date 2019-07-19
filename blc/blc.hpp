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

#include "concept/operable.hpp"

namespace blc{
	/// contain basic tools.
	namespace tools{}

	/// contain error managment class.
	namespace error{}

	/// contain networking class.
	namespace network{}

	/// contain mathematical class.
	namespace math{}

	/// contain symbolique class.
	namespace symbole{}

	/// contain all the tools to build and use constraint and concept
	namespace concept{}
}