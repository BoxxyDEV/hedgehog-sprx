#include <sys/paths.h>
#include <fstream>
#include <string>

namespace FileAPI
{
	bool isNumericChar(char x)
	{
		return (x >= '0' && x <= '9') ? true : false;
	}

	int StoI1(char *str)
	{
		if (*str == NULL)
			return 0;

		int res = 0,
			sign = 1,
			i = 0;

		if (str[0] == '-')
		{
			sign = -1;
			i++;
		}
		for (; str[i] != '\0'; ++i)
		{
			if (isNumericChar(str[i]) == false)
				return 0;
			res = res * 10 + str[i] - '0';
		}
		return sign * res;
	}

	void CreateDir(char* path)
	{
		CellFsErrno dir = cellFsMkdir(path, CELL_FS_DEFAULT_CREATE_MODE_1);
	}

	void CreateTextFile(char* path, char text[] = NULL, int size = 0)
	{
		int fd;
		char w[(uint64_t)size];
		uint64_t sw;
		CellFsErrno writeprocess;
		writeprocess = cellFsOpen(path, CELL_FS_O_RDWR | CELL_FS_O_CREAT, &fd, NULL, 0);
		memset(w, 0, (uint64_t)size);
		strcpy(w, text);
		writeprocess = cellFsWrite(fd, w, (uint64_t)size, &sw);
		writeprocess = cellFsClose(fd);
	}

	void writetofile(char* path, char* text)
	{
		int fd;
		char w[200];
		uint64_t sw;
		CellFsErrno writeprocess;
		writeprocess = cellFsOpen(path, CELL_FS_O_RDWR, &fd, NULL, 0);
		memset(w, 0, 200);
		strcpy(w, text);
		writeprocess = cellFsWrite(fd, w, 200, &sw);
		writeprocess = cellFsClose(fd);
	}

	char *ReadFile(char* path)
	{
		int fd;
		char r[50] = ""; 
		char* text;
		uint64_t sw, pos, sr, rd, read_size;
		int Readprocess;
		cellFsChmod(path, 0777);
		Readprocess = cellFsOpen(path, 0, &fd, NULL, 0);
		if (!Readprocess)
		{
			Readprocess = cellFsLseek(fd, 0, CELL_FS_SEEK_CUR, &pos);
			Readprocess = cellFsRead(fd, r, sizeof(r), &pos);
			if (!Readprocess)
			{
				Readprocess = cellFsClose(fd);
			}
		}
		text = (char*)r;
		return text;
	}

	

	bool FileExists(char* path)
	{
		int fd;
		CellFsErrno File;
		File = cellFsOpen(path, CELL_FS_O_RDWR | CELL_FS_O_CREAT, &fd, NULL, 0);
		if (File != CELL_OK)
		{
			return false;
		}
		File = cellFsClose(fd);
		return true;
	}

}