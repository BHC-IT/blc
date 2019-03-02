#pragma once

#include "blc/nonCopyable.hpp"
#include "blc/Socket.hpp"


namespace blc {
	namespace network {
		/// use two socket to différentiate from lightweight communication and huge data-transaction communication.
		class client2way : public symbole::nonCopyable {
		public:
			client2way(); ///< construct an none set object
			client2way(std::string addresse, int port, bool block = true, int mode = SOCK_STREAM, int type = AF_INET); ///< construct a set object
			~client2way();
			Socket		&getComm();
			Socket		&getData();
			std::string	getAddress() const; ///< return the adress
			int		getPort() const; ///< return the port
			bool		getBlock() const; ///< return the type of the socket (blocking/non-blocking)
			int		getMode() const; ///< return the current mode of the socket
			int		getType() const; ///< return the current type (domain) of the socket
			std::string	getAddressData() const; ///< return the adress for the data socket
			int		getPortData() const; ///< return the port for the data socket
			bool		getBlockData() const; ///< return the type for the data socket (blocking/non-blocking)
			int		getModeData() const; ///< return the current mode of the data socket
			int		getTypeData() const; ///< return the current type (domain) of the data socket
			void		setAddress(const std::string &addr); ///< set the adress. needed when empty-created
			void		setPort(int port); ///< set the port. needed when empty-created
			void		setBlock(bool block); ///< set the type of the socket. default : blocking
			void		setMode(int mode); ///< set the mode of the socket. default : SOCK_STREAM
			void		setType(int type); ///< set the type of the socket. default : AF_INETss
			void		setAddressData(const std::string &addr); ///< set the adress for data socket. needed when empty-created
			void		setPortData(int port); ///< set the port for the data socket. needed when empty-created
			void		setBlockData(bool block); ///< set the type of the data socket. default : blocking
			void		setModeData(int mode); ///< set the mode of the data socket. default : SOCK_STREAM
			void		setTypeData(int type); ///< set the type of the data socket. default : AF_INET
			void		write(const std::string &str) const; ///< write a string throught the communication socket
			void		writeData(const std::string &str) const; ///< write a string throught the data socket
			std::string	read() const; ///< read a string from the communication socket
			std::string	readData() const; ///< read a string from the data socket
			void		openComm(); ///< open the communication socket. need to be set with an address and a port.
			void		openData(); ///< open the data socket. need to be set with an address and a port.
			void		open(); ///< open both socket. need to be set with an address and a port.
			void		closeComm(); ///< close the communication socket
			void		closeData(); ///< close the data socket.
			void		close(); ///< close both sockets.
			bool		readableComm() const; ///< check if the communication socket is readable.
			bool		readableData() const; ///< check if the data socket is readable.
			bool		writeableComm() const; ///< check if the communication socket is writable.
			bool		writeableData() const; ///< check if the data socket is writable.
			bool		waitReadComm(int usec) const; ///< wait usec µsec for the communication socket to be readable.
			bool		waitReadData(int usec) const; ///< wait usec µsec for the data socket to be readable.
			bool		waitWriteComm(int usec) const; ///< wait usec µsec for the communication socket to be writable.
			bool		waitWriteData(int usec) const; ///< wait usec µsec for the data socket to be writable.
		private:
			blc::network::Socket		_comm; ///< communication socket
			blc::network::Socket		_data; ///< data socket
		};
	}
}