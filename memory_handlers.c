#include "monty.h"

/**
 * _realloc - reallocate dynamic memory
 * @old_mem_blk: pointer to the old memory block
 * @old_size: size of the old memory block
 * @new_size: size of the new memory block
 *
 * Description: The _realloc() function changes the size of the memory block
 * pointed to by @old_mem_blk to @new_size bytes. The contents will be
 * unchanged in the range from the start of the region up to the minimum of the
 * old and new sizes. If the @new_size is larger than the @old_size, the added
 * memory will not be initialized. If @old_mem_blk is NULL, then the call is
 * equivalent to @malloc(@new_size), for all values of @old_size and @new_size;
 * if @new_size is equal to zero, and @old_mem_blk ptr is not NULL, then the
 * call is equivalent to free(@old_mem_blk).
 *
 * Return: a pointer to the newly allocated memory,
 * or NULL if the request failed
 */
void *_realloc(void *old_mem_blk, size_t old_size, size_t new_size)
{
	void *new_mem_blk;
	size_t min_size;

	if (new_size == old_size)
		return (
			old_mem_blk); /* nothing to do, old and new sizes are the same */

	/* handle the free() equivalent call of the _realloc function */
	if (new_size == 0 && old_mem_blk != NULL)
	{
		monty_list.cleanup((void **)&old_mem_blk);
		return (NULL);
	}

	new_mem_blk = _calloc(new_size, sizeof(char));
	if (new_mem_blk == NULL)
		return (NULL); /* memory allocation failed */

	if (old_mem_blk != NULL)
	{
		min_size = (old_size < new_size) ? old_size : new_size;
		/* copy the data from old memory block to new memory block */
		_memcpy(new_mem_blk, old_mem_blk, min_size);

		monty_list.cleanup(
			(void **)&old_mem_blk); /* free old allocated memory block */
	}

	return (new_mem_blk);
}

/**
 * _memcpy - copy memory area
 * @dest: destination buffer
 * @src: source buffer
 * @n: number of bytes to write
 *
 * Description: The _memcpy() function copies @n bytes from memory area @src to
 * memory area @dest. The memory areas must not overlap.
 *
 * Return: A pointer to @dest
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	char *temp_dest = (char *)dest;
	const char *temp_src = (const char *)src;

	for (i = 0; i < n; i++)
	{
		temp_dest[i] = temp_src[i];
	}

	return (dest);
}

/**
 * _calloc - allocate dynamic memory
 * @nmemb: number of elements
 * @size: number of bytes to allocate
 *
 * Description: The _calloc() function allocates memory for an array of @nmemb
 * elements of @size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero. If nmemb or size is 0, then _calloc() returns
 * NULL
 *
 * Return: pointer to the allocated memory, NULL on failure.
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *new_mem;

	if (nmemb == 0 || size == 0)
		return (NULL);

	new_mem = malloc(nmemb * size);
	if (new_mem == NULL)
		return (NULL);

	/* initialize memory with zeros*/
	_memset(new_mem, 0, nmemb * size);

	return (new_mem);
}

/**
 * _memset - fill memory with constant byte
 * @mem_area: the memory area to set
 * @c: the byte to write
 * @n: the number of bytes to write
 *
 * Description: The _memset() function fills the first @n bytes of the memory
 * area pointed to by @mem_area with the constant byte @c.
 *
 * Return: a pointer to memory area @mem_area
 */
void *_memset(void *mem_area, int c, unsigned int n)
{
	unsigned int i;
	unsigned char *temp_mem_area;

	if (mem_area == NULL || n <= 0)
		return (mem_area); /* nothing to do here */

	temp_mem_area = (unsigned char *)mem_area;

	for (i = 0; i < n; i++)
		temp_mem_area[i] = c;

	return (mem_area);
}

/**
 * _free - handles the deallocation of memory
 * @ptr: a pointer to the memory address to free
 */
void _free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
