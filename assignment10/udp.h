#define MY_ID 51  // lsp51

#define SERV_UDP_PORT (8000 + MY_ID)
#define SERV_HOST_ADDR "127.0.0.1"

#define MSG_REQUEST 1
#define MSG_REPLY 2

typedef struct {
  int type;  // request or reply
  char data[128];
} MsgType;
