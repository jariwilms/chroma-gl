export module vendor.glad;

import <glad/gl.h>;

export namespace glad
{
    using bool_t            = bool          ;
    using int32_t           = int           ;
    using loader_function_t = ::GLADloadfunc;

    auto initialize(glad::loader_function_t loader_function) -> glad::int32_t
    {
        return ::gladLoadGL(loader_function);
    }
}
