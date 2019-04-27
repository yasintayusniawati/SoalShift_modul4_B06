#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

//NO 1

static const char *dirpath = "/home/yasinta/shift4";

void enkripsi(char* kata)
{
    char dasar[100] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
    for(int i=0; i<strlen(kata); i++){
        for(int j = 0 ; j<strlen(dasar); j++){
            if(kata[i] == dasar[j]){
                int indeks_baru = (j+17) % 94;
                kata[i] = dasar[indeks_baru];
                break;
            }
        }
    }
}

void dekripsi(char* kata)
{
    char dasar[100] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
    for(int i=0; i<strlen(kata); i++){
        for(int j = 0 ; j<strlen(dasar); j++){
            if(kata[i] == dasar[j]){
                int indeks_baru = (j+(94-17)) % 94;
                kata[i] = dasar[indeks_baru];
                break;
            }
        }
    }
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    ///
	char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);
	sprintf(fpath, "%s%s",dirpath,sementara);
    ///
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
	///
	char fpath[1000];

    char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
	///
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
        char file[1000];
		///
		if(strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0) dekripsi(de->d_name);
		///
        strcpy(file,de->d_name);
		res = (filler(buf, file, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
	//
  	char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
	//
	int res = 0;
	int fd = 0 ;
    
	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    ///

	res = mkdir(fpath, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;

    ///
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    ///

	(void) fi;
	fd = open(fpath, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_rename(const char *from, const char *to)
{
	int res;

    ///
    char fpathfrom[1000];
	char sementarafrom[1000];
    sprintf(sementarafrom,"%s",from);

    enkripsi(sementarafrom);
	sprintf(fpathfrom, "%s%s",dirpath,sementarafrom);
    ///

	///
    char fpathto[1000];
	char sementarato[1000];
    sprintf(sementarato,"%s",to);

    enkripsi(sementarato);
	sprintf(fpathto, "%s%s",dirpath,sementarato);
    ///

	res = rename(fpathfrom, fpathto);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	if (S_ISREG(mode)) {
		res = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (res >= 0)
			res = close(res);
	} else if (S_ISFIFO(mode))
		res = mkfifo(fpath, mode);
	else
		res = mknod(fpath, mode, rdev);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_truncate(const char *path, off_t size)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	res = truncate(fpath, size);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_unlink(const char *path)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	res = unlink(fpath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rmdir(const char *path)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	res = rmdir(fpath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	res = chmod(fpath, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	res = lchown(fpath, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	struct timeval tv[2];

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	res = utimes(fpath, tv);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
	int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

	res = open(fpath, fi->flags);
	if (res == -1)
		return -errno;

	close(res);
	return 0;
}

static int xmp_create(const char* path, mode_t mode, struct fuse_file_info* fi) {

    (void) fi;

    int res;
    //
    char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path);

    enkripsi(sementara);

	sprintf(fpath, "%s%s",dirpath,sementara);
    //

    res = creat(fpath, mode);
    if(res == -1)
	return -errno;

    close(res);

    return 0;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
    .mkdir      = xmp_mkdir,
    .write      = xmp_write,
    .rename     = xmp_rename,
    .mknod      = xmp_mknod,
    .truncate   = xmp_truncate,
    .unlink     = xmp_unlink,
    .rmdir      = xmp_rmdir,
    .chmod      = xmp_chmod,
    .chown      = xmp_chown,
    .utimens    = xmp_utimens,
    .open       = xmp_open,
    .create     = xmp_create,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}

// NO 2

// NO 3
