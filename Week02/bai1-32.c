#include <stdio.h>

typedef struct {
	int stt;
	char mssv[10], ten[64], sdt[16];
	double diem;
} sinhvien;

int main() {
	FILE *inp = fopen("bangdiem.txt", "r");
	if (!inp) {
		printf("Loi mo tep.\n");
		return 1;
	}
	FILE *out = fopen("sinhvien.dat", "wb");
	if (!out) {
		printf("Loi mo tep.\n");
		return 1;
	}
	sinhvien sv[100];
	int c;
	int i = 0;
	printf("%-8s%-16s%-32s%-20s%-6s\n", "STT", "MSSV", "Ho va ten", "SDT", "Diem");
	for (int i=0; ; i++) {
		int ret = fscanf(inp, "%d%s%s%s%lf", &sv[i].stt, sv[i].mssv, sv[i].ten, sv[i].sdt, &sv[i].diem);
		if (ret != 5) {
			break;
		}
		fwrite(&sv[i], sizeof(sv), 1, out);
		printf("%-8d%-16s%-32s%-20s%-6.2f\n", sv[i].stt, sv[i].mssv, sv[i].ten, sv[i].sdt, sv[i].diem);
		i++;
	}
	fclose(inp);
	fclose(out);
	return 0;
}
	