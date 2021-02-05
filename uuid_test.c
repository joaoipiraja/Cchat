#include <stdio.h>
#include <uuid/uuid.h>

//brew install ossp-uuid

int main(int argc, char *argv[])
{
    uuid_t uuid;

    uuid_generate_time(uuid);

    char uuid_str[37];
    uuid_unparse_lower(uuid, uuid_str);
    printf("generate uuid=%s\n", uuid_str);

    // parse (from string)
    uuid_t uuid2;
    uuid_parse(uuid_str, uuid2);

    // compare (rv == 0)
    int rv;
    rv = uuid_compare(uuid, uuid2);
    printf("uuid_compare() result=%d\n", rv);

    // compare (rv == 1)
    uuid_t uuid3;
    uuid_parse("1b4e28ba-2fa1-11d2-883f-0016d3cca427", uuid3);
    rv = uuid_compare(uuid, uuid3);
    printf("uuid_compare() result=%d\n", rv);

    // is null? (rv == 0)
    rv = uuid_is_null(uuid);
    printf("uuid_null() result=%d\n", rv);

    // is null? (rv == 1)
    uuid_clear(uuid);
    rv = uuid_is_null(uuid);
    printf("uuid_null() result=%d\n", rv);

    return 0;
}
