#pragma once
typedef char byte;
int double_compare(const void* p1, const void* p2) {
	if (*(double*)p1 > *(double*)p2)
		return 1;
	else if (*(double*)p1 < *(double*)p2)
		return -1;
	else
		return 0;
}

void merge_sort(void* base, unsigned int count, unsigned int element_size,int (*cmp)(const void*, const void*)) 
{
	for (unsigned int i = 1; i <= count; i *= 2)
	{
		byte* temp = new byte[i * 2 * element_size];
		for (unsigned int j = 0; j + i < count; j += i * 2)
		{
			unsigned int m = 0, n = 0, k = 0;
			while ( m < i && n < i && j + i + n < count)
			{
				if (cmp((byte*)base + (j + m) * element_size, (byte*)base + (j + i + n) * element_size) == 1)
				{
					for (unsigned int a = 0; a < element_size; ++a)
						temp[k++] = ((byte*)base)[(j + i + n) * element_size + a];
					++n;
				}
				else
				{
					for (unsigned int a = 0; a < element_size; ++a)
						temp[k++] = ((byte*)base)[(j + m) * element_size + a];
					++m;
				}
			}
			while (m < i)
			{
				for (unsigned int a = 0; a < element_size; ++a)
					temp[k++] = ((byte*)base)[(j + m) * element_size + a];
				++m;
			}
			while (n < i && j + i + n < count)
			{
				for (unsigned int a = 0; a < element_size; ++a)
					temp[k++] = ((byte*)base)[(j + i + n) * element_size + a];
				++n;
			}
			k = 0;
			for (unsigned int b = 0; b < 2 * i && j + b < count; ++b)
				for (unsigned int a = 0; a < element_size; ++a)
					((byte*)base)[(b + j) * element_size + a] = temp[k++];
		}
		delete []temp;
	}
}

