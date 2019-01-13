#include"TCPChatroom.h"
TCPChatRoom::TCPChatRoom(const string & chatroomName) {
    setRoomName(chatroomName);
}
void TCPChatRoom::setRoomName(const string &name) {
    roomName = name;
}
string TCPChatRoom::getRoomName() {
    return roomName;
}