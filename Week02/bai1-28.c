#include <stdio.h>

struct sinhvien {
	int stt;
	char mssv[10], name[64], sdt[16];
	double d;
};

int main() {
	FILE *inp = fopen("sinhvien.txt", "r");
	if (!inp) {
		printf("Loi mo tep.\n");
		return 1;
	}
	FILE *out = fopen("bangdiem.txt", "w");
	if (!out) {
		printf("Loi mo tep.\n");
		return 1;
	}
	struct sinhvien sv[100];
	printf("%-8s%-16s%-32s%-20s\n", "STT", "MSSV", "Ho va ten", "SDT");

	for (int i=0; ; i++) {
		int ret = fscanf(inp, "%d%s%s%s", &sv[i].stt, sv[i].mssv, sv[i].name, sv[i].sdt);
		if (ret != 4) {
			break;
		}
		printf("%-8d%-16s%-32s%-20s\n", sv[i].stt, sv[i].mssv, sv[i].name, sv[i].sdt);
		printf("Nhap diem: ");
		scanf("%lf", &sv[i].d);
		fprintf(out, "%-8d%-16s%-32s%-20s%-6.2f\n", sv[i].stt, sv[i].mssv, sv[i].name, sv[i].sdt, sv[i].d);
	}
	fclose(inp);
	return 0;
}
