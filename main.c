#include <stdio.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>
#include "pa_debug.h"

static void print_usage(char *cmd)
{
	PA_DEBUG("Password field cipher text consists of three parts: $id$salt$encrypted");
	PA_DEBUG("id to 1, using md5 encrypted");
	PA_DEBUG("id to 5, using SHA256 encrypted");
	PA_DEBUG("id to 6, using SHA512 encrypted");
	PA_DEBUG("Usage:");
	PA_DEBUG("%s root 1234 1", cmd);
}

static int i64c(int i)
{
	i &= 0x3f;
	if (i == 0)
		return '.';
	if (i == 1)
		return '/';
	if (i < 12)
		return ('0' - 2 + i);
	if (i < 38)
		return ('A' - 12 + i);
	return ('a' - 38 + i);
}

static int crypt_make_salt(char *p, int cnt, int x)
{
	x += getpid() + time(NULL);
	do {
		/**
		 * x = (x*1664525 + 1013904223) % 2^32 generator is lame
		 * (low-order bit is not "random", etc...),
		 * but for our purposes it is good enough
		 */
		x = x * 1664525 + 1013904223;
		/**
		 * BTW, Park and Miller's "minimal standard generator" is
		 * x = x*16807 % ((2^31)-1)
		 * It has no problem with visibly alternating lowest bit
		 * but is also weak in cryptographic sense + needs div,
		 * which needs more code (and slower) on many CPUs
		 */
		*p++ = i64c(x >> 16);
		*p++ = i64c(x >> 22);
	} while (--cnt);
	*p = '\0';
	return x;
}

int main(int argc, char **argv)
{
	char salt[sizeof("$N$XXXXXXXX")];  // "$N$XXXXXXXX" or "XX"
	char *crypt_return_str = NULL;

	PA_INFO("create_passwd --> main");

	if (argc != 4) {
		print_usage(argv[0]);
		return -1;
	}
	PA_DEBUG("user: %s", argv[1]);
	PA_DEBUG("passwd: %s", argv[2]);

	/**
	 * 密码域密文也是由三部分组成的，即：$id$salt$encrypted。
	 * id为1时，采用md5进行加密；
	 * id为5时，采用SHA256进行加密；
	 * id为6时，采用SHA512进行加密。
	 */
	sprintf(salt, "$%s$", argv[3]);
	crypt_make_salt(salt + 3, 4, 0);
	crypt_return_str = crypt(argv[2], salt);
	PA_DEBUG("salt: %s", salt);
	PA_DEBUG("crypt: %s", crypt_return_str);

	return 0;
}
