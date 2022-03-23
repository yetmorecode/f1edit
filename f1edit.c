#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	uint32_t offset;
	uint32_t size;
	uint16_t extra;
	char name[14];
} entry;

int main (int ac, char**av) {
	FILE *file = fopen(av[1], "rb");

	unsigned int a, b;
	fread(&a, 4, 1, file);
	fread(&b, 4, 1, file);

	entry e;
	FILE *index = fopen("3d\\_index.txt", "w");
	for (int i=0; i < a; i++) {
		fread(&e, sizeof(e), 1, file);
		fprintf(index, "%13s: offset = %06x, length = %06d, extra = %04x\n", e.name, e.offset, e.size, e.extra);

		char name[256];
		sprintf(name, "3d\\%s", e.name);
		FILE  *out = fopen(name, "wb");
		char *buf = (char*)malloc(e.size);
		long pos = ftell(file);
		fseek(file, e.offset, SEEK_SET);
		fread(buf, e.size, 1, file);
		fseek(file, pos, SEEK_SET);
		fwrite(buf, e.size, 1, out);
		free(buf);
		fclose(out);
	}
	printf("%d total\n", a);
	fclose(file);

	return 0;
}
