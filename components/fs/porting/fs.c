/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define _GNU_SOURCE

#include <errno.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <unistd.h>
#include "prt_fs.h"

int mount(const char *source, const char *target,
          const char *filesystemtype, unsigned long mountflags,
          const void *data)
{
    return PRT_FsMount(source, target, filesystemtype, mountflags, data);
}

int umount(const char *target)
{
    return PRT_FsUmount(target);
}

int umount2(const char *target, int flag)
{
    return PRT_FsUmount2(target, flag);
}

int open(const char *path, int oflag, ...)
{
    va_list vaList;
    va_start(vaList, oflag);
    int ret;
    ret = PRT_Open(path, oflag, vaList);
    va_end(vaList);
    return ret;
}

int close(int fd)
{
    return PRT_Close(fd);
}

ssize_t read(int fd, void *buf, size_t nbyte)
{
    return PRT_Read(fd, buf, nbyte);
}

ssize_t write(int fd, const void *buf, size_t nbyte)
{
    return PRT_Write(fd, buf, nbyte);
}

off_t lseek(int fd, off_t offset, int whence)
{
    return PRT_Lseek(fd, offset, whence);
}

int unlink(const char *path)
{
    return PRT_Unlink(path);
}

int fstat(int fd, struct stat *buf)
{
    return PRT_Fstat(fd, buf);
}

int stat(const char *path, struct stat *buf)
{
    return PRT_Stat(path, buf);
}

int fsync(int fd)
{
    return PRT_Fsync(fd);
}

int mkdir(const char *__path, mode_t mode)
{
    return PRT_Mkdir(__path, mode);
}

DIR *opendir(const char *dirName)
{
    return PRT_Opendir(dirName);
}

struct dirent *readdir(DIR *dir)
{
    return PRT_Readdir(dir);
}

int closedir(DIR *dir)
{
    return PRT_Closedir(dir);
}

int rmdir(const char *path)
{
    return PRT_Unlink(path);
}

int rename(const char *oldName, const char *newName)
{
    return PRT_Rename(oldName, newName);
}

int statfs(const char *path, struct statfs *buf)
{
    return PRT_Statfs(path, buf);
}

int ftruncate(int fd, off_t length)
{
    return PRT_Ftruncate(fd, length);
}

ssize_t pread(int fd, void *buf, size_t nbyte, off_t offset)
{
    return PRT_Pread(fd, buf, nbyte, offset);
}

ssize_t pwrite(int fd, const void *buf, size_t nbyte, off_t offset)
{
    return PRT_Pwrite(fd, buf, nbyte, offset);
}

int access(const char *path, int mode)
{
    struct stat st;

    if (stat(path, &st) < 0) {
        return -1;
    }
    if ((st.st_mode & S_IFDIR) || (st.st_mode & S_IFREG)) {
        return 0;
    }
    if ((mode & W_OK) && !(st.st_mode & S_IWRITE)) {
        return -1;
    }

    return 0;
}