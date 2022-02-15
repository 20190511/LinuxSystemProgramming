#define MY_ID 51  // lsp51
#define SHM_KEY (0x9000 + MY_ID)
#define SHM_SIZE 1024
#define SHM_MODE (SHM_R | SHM_W | IPC_CREAT)  // rw + create
