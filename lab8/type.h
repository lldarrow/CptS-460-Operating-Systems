/******************************************
Luke Darrow 11349190
Cpts 460
type.h
contains most of the type definitions
******************************************/

typedef unsigned char   u8;
typedef unsigned short u16;
typedef unsigned long  u32;
typedef unsigned short ushort;
typedef unsigned long ulong;

#define NULL     0
#define NPROC    9
#define SSIZE 1024

/******* PROC status ********/
#define FREE     0
#define READY    1
#define RUNNING  2
#define STOPPED  3
#define SLEEP    4
#define ZOMBIE   5
#define BLOCK    6

#define READ_PIPE 4
#define WRITE_PIPE 5

#define NOFT 20
#define NFD 10

//piping data structures
typedef struct oft{
	int mode; //READ, WRITE
	int refCount;
	struct pipe *pipe_ptr;
	
}OFT;

#define PSIZE 10
#define NPIPE 10

typedef struct pipe{
	char buf[PSIZE];
	int head, tail, data, room;
	int nreader, nwriter;	//number of readers, writers
	int busy;	//IN_USE or FREE
}PIPE;

typedef struct proc{
    struct proc *next;
    int    *ksp;               // at offset 2 bytes
    int    uss, usp;           // at offsets 4,6
    int    inkmode;            // at offset 8

    int    pid;                // add pid for identify the proc
    int    status;             // status = FREE|READY|RUNNING|SLEEP|ZOMBIE    
    int    ppid;               // parent pid
    struct proc *parent;
    int    priority;
    int    event;
    int    exitCode;
    char   name[32];           // name string of PROC
    int time;
    struct semaphore *sem;

    OFT *fd[NFD];		//ADD: open file descriptors

    int    kstack[SSIZE];      // per proc stack area
}PROC;

/*********** EXT2 FS types for loader.c ******************/
//INODE struct
typedef struct ext2_inode {
	u16	i_mode;		/* File mode */
	u16	i_uid;		/* Owner Uid */
	u32	i_size;		/* Size in bytes */
	u32	i_atime;	/* Access time */
	u32	i_ctime;	/* Creation time */
	u32	i_mtime;	/* Modification time */
	u32	i_dtime;	/* Deletion Time */
	u16	i_gid;		/* Group Id */
	u16	i_links_count;	/* Links count */
	u32	i_blocks;	/* Blocks count */
	u32	i_flags;	/* File flags */
        u32     dummy;
	u32	i_block[15];    /* Pointers to blocks */
        u32     pad[7];         /* inode size MUST be 128 bytes */
} INODE;

//group descriptor struct
typedef struct ext2_group_desc
{
	u32	bg_block_bitmap;		/* Blocks bitmap block */
	u32	bg_inode_bitmap;		/* Inodes bitmap block */
	u32	bg_inode_table;		/* Inodes table block */
	u16	bg_free_blocks_count;	/* Free blocks count */
	u16	bg_free_inodes_count;	/* Free inodes count */
	u16	bg_used_dirs_count;	/* Directories count */
	u16	bg_pad;
	u32	bg_reserved[3];
} GD;

//directory struct
typedef struct ext2_dir_entry_2 {
	u32	inode;			/* Inode number */
	u16	rec_len;		/* Directory entry length */
	u8	name_len;		/* Name length */
	u8	file_type;
	char	name[255];      	/* File name */
} DIR;
