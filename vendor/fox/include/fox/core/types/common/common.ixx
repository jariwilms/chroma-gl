export module fox.core.types.common;

import fox.core.types.fundamental;

export namespace fox
{
	using byte_t   = fox::uint8_t ;
	using size_t   = fox::uint64_t; //Number of bytes
	using offset_t = fox::uint64_t; //Number of bytes offset
	using count_t  = fox::uint32_t; //Number of elements
	using index_t  = fox::uint32_t; //Number of elements offset
	using hash_t   = fox::size_t  ;
}