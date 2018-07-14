#include <stdio.h>
#include "pa_debug.h"

void print_usage(char *cmd)
{
	PA_DEBUG("Password field cipher text consists of three parts: $id$salt$encrypted");
	PA_DEBUG("id to 1, using md5 encrypted");
	PA_DEBUG("id to 5, using SHA256 encrypted");
	PA_DEBUG("id to 6, using SHA512 encrypted");
	PA_DEBUG("Usage:");
	PA_DEBUG("%s root 1234 1", cmd);
}

int main(int argc, char **argv)
{
	char salt[sizeof("$N$XXXXXXXX")];  /* "$N$XXXXXXXX" or "XX" */

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
	PA_DEBUG("salt: %s", salt);

	return 0;
}
