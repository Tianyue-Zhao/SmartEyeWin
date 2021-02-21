#include <windows.h>
#include <wingdi.h>

bool set_gamma(int r, int g, int b, HDC context)
{
	WORD gamma_array[3][256];
	int i;
	for (i = 0;i < 256;i++)
	{
		gamma_array[0][i] = r * i;
		gamma_array[1][i] = g * i;
		gamma_array[2][i] = b * i;
	}
	return SetDeviceGammaRamp(context, gamma_array);
}