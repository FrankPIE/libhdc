/*
* Copyright (C) 2021 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <assert.h>
#include <stdbool.h>

#include <serial/serial.h>

#include <common/errorc.h>

#include <Windows.h>

struct _serial_handle_t
{
	HANDLE  serial_port;
};

struct _serial_handle_t* init_handle()
{
	struct _serial_handle_t* handle = (struct _serial_handle_t*)malloc(sizeof(struct _serial_handle_t));

	if (handle)
	{
		handle->serial_port = INVALID_HANDLE_VALUE;
	}

	return handle;
}

void destroy_handle(struct _serial_handle_t* handle)
{
	if (handle)
	{
		if (handle->serial_port != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle->serial_port);
		}

		free(handle);
	}
}

bool baud_check_available(int baud)
{
	switch (baud)
	{
	case CBR_110:
	case CBR_300:
	case CBR_600:
	case CBR_1200:
	case CBR_2400:
	case CBR_4800:
	case CBR_9600:
	case CBR_14400:
	case CBR_19200:
	case CBR_38400:
	case CBR_56000:
	case CBR_57600:
	case CBR_115200:
	case CBR_128000:
	case CBR_256000:
		return true;

	default:
		return false;

	}
}

bool databits_check_available(int databits)
{
	return (databits >= 5) && (databits <= 8);
}

bool stopbits_check_available(int stopbits)
{
	return (stopbits >= 0) && (stopbits <= 2);
}

bool parity_check_available(int parity)
{
	return (parity >= 0) && (parity <= 2);
}

bool dtr_check_available(int dtr)
{
	return (dtr >= 0) && (dtr <= 2);
}

bool rts_check_available(int rts)
{
	return (rts >= 0) && (rts <= 3);
}

int serial_device_open(serial_handle_t** handle, const char* serial_device)
{
	assert(serial_device != NULL);

	if (serial_device == NULL)
		return HDC_EC_ERROR_PARAMETER;

	*handle = init_handle();

	(*handle)->serial_port = CreateFileA(serial_device,
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 
		0, NULL);

	if ((*handle)->serial_port == INVALID_HANDLE_VALUE)
		return HDC_EC_CREATE_DEVICE_HANDLE_FAILED;

	return HDC_SUCCESS;
}

int serial_device_set(serial_handle_t* handle, hdc_serial_device_property property, const void* value)
{
	assert(handle);

	if (handle->serial_port == INVALID_HANDLE_VALUE)
		return HDC_EC_INVALID_DEVICE_HANDLE;

	DCB dcb;
	if (!GetCommState(handle->serial_port, &dcb))
		return HDC_EC_INVALID_DEVICE_HANDLE;

	switch (property) {
	case SERIAL_DEVICE_BAUD:
		{
			const int baud = *(int*)value;

			if (!baud_check_available(baud))
				return HDC_EC_ERROR_PARAMETER;

			dcb.BaudRate = baud;
		}
		break;

	case SERIAL_DEVICE_DATABITS:
		{
			const int databits = *(int*)value;

			if (!databits_check_available(databits))
				return HDC_EC_ERROR_PARAMETER;

			dcb.ByteSize = databits;
		}
		break;

	case SERIAL_DEVICE_STOPBITS:
		{
			const int stopbits = *(int*)value;

			if (!stopbits_check_available(stopbits))
				return HDC_EC_ERROR_PARAMETER;
			
			dcb.StopBits = (BYTE)stopbits;
		}
		break;

	case SERIAL_DEVICE_PARITY:
		{
			const int parity = *(int*)value;

			if (!parity_check_available(parity))
				return HDC_EC_ERROR_PARAMETER;

			dcb.Parity = (BYTE)parity;
		}
		break;

	case SERIAL_DEVICE_DTR:
		{
			const int dtr = *(int*)value;
			
			if (!dtr_check_available(dtr))
				return HDC_EC_ERROR_PARAMETER;

			dcb.fDtrControl = (DWORD)(dtr);
		}
		break;

	case SERIAL_DEVICE_RTS:
		{
			const int rts = *(int*)value;

			if (!rts_check_available(rts))
				return HDC_EC_ERROR_PARAMETER;

			dcb.fRtsControl = (DWORD)(rts);
		}
		break;

	default:
		return HDC_EC_ERROR_PARAMETER;
	}

	SetCommState(handle->serial_port, &dcb);

	return HDC_SUCCESS;

}

int serial_device_get(serial_handle_t* handle, hdc_serial_device_property property, void* value)
{
	assert(handle);

	DCB dcb;
	if (!GetCommState(handle->serial_port, &dcb))
		return HDC_EC_INVALID_DEVICE_HANDLE;

	switch (property) {
	case SERIAL_DEVICE_BAUD:
		{
			*(int*)value = dcb.BaudRate;
		}
		break;

	case SERIAL_DEVICE_DATABITS:
		{
			*(int*)value = dcb.ByteSize;
		}
		break;

	case SERIAL_DEVICE_STOPBITS:
		{
			*(int*)value = dcb.StopBits;
		}
		break;

	case SERIAL_DEVICE_PARITY:
		{
			*(int*)value = dcb.Parity;
		}
		break;

	case SERIAL_DEVICE_DTR:
		{
			*(int*)value = dcb.fDtrControl;
		}
		break;

	case SERIAL_DEVICE_RTS:
		{
			*(int*)value = dcb.fRtsControl;
		}
		break;

	default:
		return HDC_EC_ERROR_PARAMETER;
	}

	return HDC_SUCCESS;
}

int serial_device_send(serial_handle_t* handle, const void* data, size_t size, size_t* send_size)
{
	assert(handle);

	if (handle->serial_port == INVALID_HANDLE_VALUE)
		return HDC_EC_INVALID_DEVICE_HANDLE;

	DWORD bytes_written;
	if (!WriteFile(handle->serial_port, data, size, &bytes_written, NULL))
		return HDC_EC_WRITE_FAILED;

	*send_size = bytes_written;

	return HDC_SUCCESS;
}

int serial_device_receive(serial_handle_t* handle, void* buffer, size_t buffer_size, size_t* receive_size)
{
	assert(handle);

	if (handle->serial_port == INVALID_HANDLE_VALUE)
		return HDC_EC_INVALID_DEVICE_HANDLE;

	DWORD recsz;
	if (!ReadFile(handle->serial_port, buffer, buffer_size, &recsz, NULL))
		return HDC_EC_READ_FAILED;

	*receive_size = recsz;

	return HDC_SUCCESS;
}

void serial_device_close(serial_handle_t* handle)
{
	destroy_handle(handle);
}
