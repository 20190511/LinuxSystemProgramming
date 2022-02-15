#define MY_ID 51  // lsp51
#define MSG_KEY (0x8000 + MY_ID)

#define MSG_REQUEST 1
#define MSG_REPLY 2

typedef struct {
  long type;
  char data[128];
} MsgType;
