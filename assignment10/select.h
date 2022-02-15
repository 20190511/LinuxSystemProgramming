#define MY_ID 51  // lsp51

#define SERV_TCP_PORT (7000 + MY_ID)
#define SERV_UDP_PORT (8000 + MY_ID)
#define UNIX_STR_PATH "./.unix-str"
#define UNIX_DG_PATH "./.unix-dg"

#define MSG_REQUEST 1
#define MSG_REPLY 2

typedef struct {
  int type;
  char data[128];
} MsgType;
