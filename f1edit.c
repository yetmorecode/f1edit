#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <direct.h>

typedef struct {
	uint32_t offset;
	uint32_t size;
	uint16_t dir;
	char name[14];
} file_entry;

typedef struct {
	char name[80];
} dir_entry;

int main (int ac, char**av) {
	FILE *file = fopen(av[1], "rb");

	int files, directories;
	fread(&files, 4, 1, file);
	fread(&directories, 4, 1, file);

	file_entry *entries = (file_entry*)malloc(sizeof(file_entry)*files);
	fread(entries, sizeof(file_entry), files, file);
	dir_entry *dirs = (dir_entry*)malloc(sizeof(dir_entry)*directories);
	fread(dirs, sizeof(dir_entry), directories, file);
	FILE *index = fopen("3D\\index.txt", "w");
	for (int i=0; i < directories; i++) {
		mkdir(dirs[i].name);
	}
	for (int i=0; i < files; i++) {
	    	file_entry *e = entries+i;
		fprintf(index, "%s\\%13s: offset = %06x, length = %06d\n",
			dirs[e->dir].name,
			e->name, e->offset, e->size);
		char name[256];
		sprintf(name, "%s\\%s", dirs[e->dir].name, e->name);
		//printf("%s\n", name);
		FILE  *out = fopen(name, "wb");
		char *buf = (char*)malloc(e->size);
		fseek(file, e->offset, SEEK_SET);
		fread(buf, e->size, 1, file);
		fwrite(buf, e->size, 1, out);
		free(buf);
		fclose(out);
	}
	printf("%d files, %d directories\n", files, directories);
	fclose(file);

	return 0;
}
