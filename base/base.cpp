#include <base.h>

//////////////////////////////////
// Note: Symbolic Constant Functions

function OperatingSystem operating_system_from_context(void)
{
    OperatingSystem result = OperatingSystem_Null;
#if OS_WINDOWS
    result = OperatingSystem_Windows;
#elif OS_LINUX
    result = OperatingSystem_Linux;
#elif OS_MAC
    result = OperatingSystem_Mac;
#endif
return result;
}
function Architecture architexture_from_context(void)
{
    Architecture result = Architecture_Null;
#if ARCH_X64
    result = Architecture_X86;
#elif ARCH_X86
    result = Architecture_X86;
#elif ARCH_ARM
    result = Architecture_ARM;
#elif ARCH_ARM64
    result = Architecture_ARM64;
#endif
return result;
}

function char* string_from_operating_system(OperatingSystem os)
{
    char* result = "(null)";

    switch (os)
    {
        case OperatingSystem_Windows:
        {
            result = "windows";
        }break;
        case OperatingSystem_Linux:
        {
            result = "linux";
        }break;
        case OperatingSystem_Mac:
        {
            result = "mac";
        }break;
    }
    return result;
}
function char* string_from_architecture(Architecture arch)
{
    char* result = "(null)";

    switch (arch)
    {
        case Architecture_X64:
        {
            result = "x64";
        }break;
        case Architecture_X86:
        {
            result = "x86";
        }break;
        case Architecture_ARM:
        {
            result = "ARM";
        }break;
        case Architecture_ARM64:
        {
            result = "ARM64";
        }break;
    }
    return result;
}
function char* string_from_month(Month month)
{
    char* result = "(null)";

    switch (month)
    {
        case Month_Jan:
        {
            result = "Jan";
        }break;
        case Month_Feb:
        {
            result = "Feb";
        }break;
        case Month_Mar:
        {
            result = "Mar";
        }break;
        case Month_Apr:
        {
            result = "Apr";
        }break;
        case Month_May:
        {
            result = "May";
        }break;
        case Month_Jun:
        {
            result = "Jun";
        }break;
        case Month_Jul:
        {
            result = "Jul";
        }break;
        case Month_Aug:
        {
            result = "Aug";
        }break;
        case Month_Sep:
        {
            result = "Sep";
        }break;
        case Month_Oct:
        {
            result = "Oct";
        }break;
        case Month_Nov:
        {
            result = "Nov";
        }break;
        case Month_Dec:
        {
            result = "Dec";
        }break;
    }
    return result;
}
function char* string_from_day_of_week(DayOfWeek day_of_week)
{
    char* result = "(null)";

    switch (day_of_week)
    {
        case DayOfWeek_Sunday:
        {
            result = "Sunday";
        }break;
        case DayOfWeek_Monday:
        {
            result = "Monday";
        }break;
        case DayOfWeek_Tuesday:
        {
            result = "Tuesday";
        }break;
        case DayOfWeek_Wednesday:
        {
            result = "Wednesday";
        }break;
        case DayOfWeek_Thursday:
        {
            result = "Thursday";
        }break;
        case DayOfWeek_Friday:
        {
            result = "Friday";
        }break;
        case DayOfWeek_Saturday:
        {
            result = "Saturday";
        }break;
    }
    return result;
}

//////////////////////////////////
// Note: Float Constant Functions

function F32
inf_F32(void)
{
    union{F32 f; U32 u;} r;
    r.u = 0x7f800000;
    return r.f;
}

function F32
neg_inf_F32(void)
{
    union{F32 f; U32 u;} r;
    r.u = 0xff800000;
    return r.f;
}

function F64 
inf_F64(void)
{
    union{F64 f; U64 u;} r;
    r.u = 0x7ff0000000000000;
    return r.f;
}

function F64 
neg_inf_F64(void)
{
    union{F64 f; U64 u;} r;
    r.u = 0xfff0000000000000;
    return r.f;
}

//////////////////////////////////
// Note: Math Functions

function F32 
abs_F32(F32 x)
{
    union{F32 f; U32 u;} r;
    r.f= x;
    r.u &= 0x7fffffff;
    return r.f;
}

function F64 
abs_F64(F64 x)
{
    union{F64 f; U64 u;} r;
    r.f= x;
    r.u &= 0x7fffffffffffffff;
    return r.f;
}

#include <math.h>

function F32 sqrt_F32(F32 x)
{
    return(sqrt(x));
}
function F32 sin_F32(F32 x)
{
    return(sin(x));
}
function F32 cos_F32(F32 x)
{
    return(cos(x));
}
function F32 tan_F32(F32 x)
{
    return(tan(x));
}
function F32 ln_F32(F32 x)
{
    return(logf(x));
}

function F64 sqrt_F64(F64 x)
{
    return(sqrt(x));
}
function F64 sin_F64(F64 x)
{
    return(sin(x));
}
function F64 cos_F64(F64 x)
{
    return(cos(x));
}
function F64 tan_F64(F64 x)
{
    return(tan(x));
}
function F64 ln_F64(F64 x)
{
    return(log(x));
}

function F32 lerp_F32(F32 a, F32 b, F32 dx)
{
    F32 x = a + (b - a) * dx;
    return x;
}
function F32 unLerp_F32(F32 a, F32 b, F32 x)
{
    F32 dx = 0.f;

    if(a != b)
    {
        dx = (x - a) / (b - a);
    }
    return dx;
}

function F64 lerp_F64(F64 a, F64 b, F64 dx)
{
    F64 x = a + (b -a) * dx;
}
function F64 unLerp_F64(F64 a, F64 b, F64 x)
{
    F64 dx = 0.;

    if(a != b)
    {
        dx = (x-a)/(b-a);
    }
    return dx;
}

//////////////////////////////////
// Note: Compound Type functions

// constructors
function V2S32 v2s32(S32 x, S32 y)
{
    return V2S32{x, y};
}

function V2F32 v2F32(F32 x, F32 y)
{
    return V2F32{x, y};
}
function V3F32 v3F32(F32 x, F32 y, F32 z)
{
    return V3F32{x, y, z};
}
function V4F32 v4F32(F32 x, F32 y, F32 z, F32 w)
{
    return V4F32{x, y, z, w};
}

function V2F64 v2F64(F64 x, F64 y)
{
    return V2F64{x, y};
}
function V3F64 v3F64(F64 x, F64 y, F64 z)
{
    return V3F64{x, y, z};
}
function V4F64 v4F64(F64 x, F64 y, F64 z, F64 w)
{
    return V4F64{x, y, z, w};
}

function I1U64 i1U64(U64 min, U64 max)
{
    I1U64 r = {min, max};
    if(max < min)
    {
        r.max=min;
        r.min=max;
    }
    return r;
}
function I1S32 i1S32(S32 min, S32 max)
{
    I1S32 r = {min, max};
    if(max < min)
    {
        r.max=min;
        r.min=max;
    }
    return r;
}
function I1F32 i1F32(F32 min, F32 max)
{
    I1F32 r = {min, max};
    if(max < min)
    {
        r.max = min;
        r.min = max;
    }
    return r;
}
function I1F64 i1F64(F64 min, F64 max)
{
    I1F64 r = {min, max};
    if(max < min)
    {
        r.max = min;
        r.min = max;
    }
    return r;
}

function I2S32 i2S32(S32 x0, S32 y0, S32 x1, S32 y1)
{
    I2S32 r = {x0, y0, x1, y1};
    if(x1 < x0)
    {
        r.x1 = x0;
        r.x0 = x1;
    }
    if(y1 < y0)
    {
        r.y1 = y0;
        r.y0 = y1;
    }
    return r;
}
function I2S32 i2S32_range(I1S32 x, I1S32 y)
{
    return i2S32(x.min, y.min, x.max, y.max);
}
function I2S32 i2S32_vec(V2S32 min, V2S32 max)
{
    return i2S32(min.x, min.y, max.x, max.y);
}


function I2F32 i2F32(F32 x0, F32 y0, F32 x1, F32 y1)
{
    I2F32 r = {x0, y0, x1, y1};
    if(x1 < x0)
    {
        r.x1 = x0;
        r.x0 = x1;
    }
    if(y1 < y0)
    {
        r.y1 = y0;
        r.y0 = y1;
    }
    return r;
}
function I2F32 i2F32_range(I1F32 x, I1F32 y)
{
    return i2F32(x.min, y.min, x.max, y.max);
}
function I2F32 i2F32_vec(V2F32 min, V2F32 max)
{
    return i2F32(min.x, min.y, max.x, max.y);
}

function I2F64 i2F64(F64 x0, F64 y0, F64 x1, F64 y1)
{
    I2F64 r = {x0, y0, x1, y1};
    if(x1 < x0)
    {
        r.x1 = x0;
        r.x0 = x1;
    }
    if(y1 < y0)
    {
        r.y1 = y0;
        r.y0 = y1;
    }
    return r;
}
function I2F64 i2F64_range(I1F64 x, I1F64 y)
{
    return i2F64(x.min, y.min, x.max, y.max);
}
function I2F64 i2F64_vec(V2F64 min, V2F64 max)
{
    return i2F64(min.x, min.y, max.x, max.y);
}

// vector addition operations
function V2S32 operator+(const V2S32 &a, const V2S32 &b)
{
    return V2S32{(a.x+b.x), (a.y+b.y)};
}

function V2F32 operator+(const V2F32 &a, const V2F32 &b)
{
    return V2F32{(a.x+b.x), (a.y+b.y)};
}
function V3F32 operator+(const V3F32 &a, const V3F32 &b)
{
    return V3F32{(a.x+b.x), (a.y+b.y), (a.z+b.z)};
}
function V4F32 operator+(const V4F32 &a, const V4F32 &b)
{
    return V4F32{(a.x+b.x), (a.y+b.y), (a.z+b.z), (a.w+b.w)};
}

function V2F64 operator+(const V2F64 &a, const V2F64 &b)
{
    return V2F64{(a.x+b.x), (a.y+b.y)};
}
function V3F64 operator+(const V3F64 &a, const V3F64 &b)
{
    return V3F64{(a.x+b.x), (a.y+b.y), (a.z+b.z)};
}
function V4F64 operator+(const V4F64 &a, const V4F64 &b)
{
    return V4F64{(a.x+b.x), (a.y+b.y), (a.z+b.z), (a.w+b.w)};
}

// vector subtraction operations
function V2S32 operator-(const V2S32 &a, const V2S32 &b)
{
    return V2S32{(a.x-b.x), (a.y-b.y)};
}

function V2F32 operator-(const V2F32 &a, const V2F32 &b)
{
    return V2F32{(a.x-b.x), (a.y-b.y)};
}
function V3F32 operator-(const V3F32 &a, const V3F32 &b)
{
    return V3F32{(a.x-b.x), (a.y-b.y), (a.z-b.z)};
}
function V4F32 operator-(const V4F32 &a, const V4F32 &b)
{
    return V4F32{(a.x-b.x), (a.y-b.y), (a.z-b.z), (a.w-b.w)};
}

function V2F64 operator-(const V2F64 &a, const V2F64 &b)
{
    return V2F64{(a.x-b.x), (a.y-b.y)};
}
function V3F64 operator-(const V3F64 &a, const V3F64 &b)
{
    return V3F64{(a.x-b.x), (a.y-b.y), (a.z-b.z)};
}
function V4F64 operator-(const V4F64 &a, const V4F64 &b)
{
    return V4F64{(a.x-b.x), (a.y-b.y), (a.z-b.z), (a.w-b.w)};
}

// vector multiplication operations
function V2S32 operator*(const V2S32 &a, const S32 &c)
{
    return V2S32{a.x*c, a.y*c};
}

function V2F32 operator*(const V2F32 &a, const F32 &c)
{
    return V2F32{a.x*c, a.y*c};
}
function V3F32 operator*(const V3F32 &a, const F32 &c)
{
    return V3F32{a.x*c, a.y*c, a.z*c};
}
function V4F32 operator*(const V4F32 &a, const F32 &c)
{
    return V4F32{a.x*c, a.y*c, a.z*c, a.w*c};
}

function V2F64 operator*(const V2F64 &a, const F64 &c)
{
    return V2F64{a.x*c, a.y*c};
}
function V3F64 operator*(const V3F64 &a, const F64 &c)
{
    return V3F64{a.x*c, a.y*c, a.z*c};
}
function V4F64 operator*(const V4F64 &a, const F64 &c)
{
    return V4F64{a.x*c, a.y*c, a.z*c, a.w*c};
}

// vector dot operations
function F32 vec_dot(V2F32 a, V2F32 b)
{
    return a.x*a.y + a.y*b.y;
}
function F32 vec_dot(V3F32 a, V3F32 b)
{
    return a.x*a.y + a.y*b.y + a.z*b.z;
}
function F32 vec_dot(V4F32 a, V4F32 b)
{
    return a.x*a.y + a.y*b.y + a.z*b.z + a.w*b.w;
}

function F64 vec_dot(V2F64 a, V2F64 b)
{
    return a.x*a.y + a.y*b.y;
}
function F64 vec_dot(V3F64 a, V3F64 b)
{
    return a.x*a.y + a.y*b.y + a.z*b.z;
}
function F64 vec_dot(V4F64 a, V4F64 b)
{
    return a.x*a.y + a.y*b.y + a.z*b.z + a.w*b.w;
}

// vector cross operations
function F32 vec_cross_2D(V2F32 a, V2F32 b)
{
    return a.x*b.y-a.y*b.x;
}
function V2F32 naive_2D_cross(V2F32 a)
{
    return V2F32{a.y, -a.x};
}
function V3F32 vec_cross(V3F32 a, V3F32 b)
{
    V3F32 r = V3F32{a.y*b.z-b.y*a.z, 
                a.z*b.x-b.z*a.x, 
                a.x*b.y-b.x*a.y};
    return r;
}
function V4F32 vec_cross(V4F32 a, V4F32 b, V4F32 c)
{
    V4F32 r = V4F32{b.z*(a.y*c.w-a.w*c.y), 
                b.w*(a.z*c.x-a.x*c.z), 
                b.x*(a.w*c.y-a.y*c.w),
                b.y*(a.x*c.z-a.z*c.x)};
    return r;
}

function F64 vec_cross_2D(V2F64 a, V2F64 b)
{
    return a.x*b.y-a.y*b.x;
}
function V2F64 naive_2D_cross(V2F64 a)
{
    return V2F64{a.y, -a.x};
}
function V3F64 vec_cross(V3F64 a, V3F64 b)
{
    V3F64 r = V3F64{a.y*b.z-b.y*a.z, 
                a.z*b.x-b.z*a.x, 
                a.x*b.y-b.x*a.y};
    return r;
}
function V4F64 vec_cross(V4F64 a, V4F64 b, V4F64 c)
{
    V4F64 r = V4F64{b.z*(a.y*c.w-a.w*c.y), 
                b.w*(a.z*c.x-a.x*c.z),
                b.x*(a.w*c.y-a.y*c.w),
                b.y*(a.x*c.z-a.z*c.x)};
    return r;
}

// hadamard (naieve matrix multiplication) operations
function V2S32 vec_hadamard(V2S32 a, V2S32 b)
{
    return V2S32{a.x*a.y, a.y*b.y};
}

function V2F32 vec_hadamard(V2F32 a, V2F32 b)
{
    return V2F32{a.x*a.y, a.y*b.y};
}
function V3F32 vec_hadamard(V3F32 a, V3F32 b)
{
    return V3F32{a.x*a.y, a.y*b.y, a.z*b.z};
}
function V4F32 vec_hadamard(V4F32 a, V4F32 b)
{
    return V4F32{a.x*a.y, a.y*b.y, a.z*b.z, a.w*b.w};
}

function V2F64 vec_hadamard(V2F64 a, V2F64 b)
{
    return V2F64{a.x*a.y, a.y*b.y};
}
function V3F64 vec_hadamard(V3F64 a, V3F64 b)
{
    return V3F64{a.x*a.y, a.y*b.y, a.z*b.z};
}
function V4F64 vec_hadamard(V4F64 a, V4F64 b)
{
    return V4F64{a.x*a.y, a.y*b.y, a.z*b.z, a.w*b.w};
}

// interval overlaps
function B32 intr_overlaps(I1U64 a, I1U64 b)
{
    B32 overlaps = (a.min < b.max) || (b.min < a.max);
    return overlaps;
}
function B32 intr_overlaps(I1S32 a, I1S32 b)
{
    B32 overlaps = (a.min < b.max) || (b.min < a.max);
    return overlaps;
}
function B32 intr_overlaps(I1F32 a, I1F32 b)
{
    B32 overlaps = (a.min < b.max) || (b.min < a.max);
    return overlaps;
}
function B32 intr_overlaps(I1F64 a, I1F64 b)
{
    B32 overlaps = (a.min < b.max) || (b.min < a.max);
    return overlaps;
}

function B32 intr_overlaps(I2S32 a, I2S32 b)
{
    B32 overlaps = (b.x0 < a.x1) && (b.y0 < a.y1)
                 &&(a.x0 < b.x1) && (a.y0 < b.y1);
    return overlaps;
}
function B32 intr_overlaps(I2F32 a, I2F32 b)
{
    B32 overlaps = (b.x0 < a.x1) && (b.y0 < a.y1)
                 &&(a.x0 < b.x1) && (a.y0 < b.y1);
    return overlaps;
}
function B32 intr_overlaps(I2F64 a, I2F64 b)
{
    B32 overlaps = (b.x0 < a.x1) && (b.y0 < a.y1)
                 &&(a.x0 < b.x1) && (a.y0 < b.y1);
    return overlaps;
}

// interval contains
function B32 intr_contains(I1U64 r, U64 p)
{
    B32 contains = (r.min <= p) && (r.max > p);
    return contains;
}
function B32 intr_contains(I1S32 r, S32 p)
{
    B32 contains = (r.min <= p) && (r.max > p);
    return contains;
}
function B32 intr_contains(I1F32 r, F32 p)
{
    B32 contains = (r.min <= p) && (r.max > p);
    return contains;
}
function B32 intr_contains(I1F64 r, F64 p)
{
    B32 contains = (r.min <= p) && (r.max > p);
    return contains;
}

function B32 intr_contains(I2S32 r, V2S32 p)
{
    B32 contains = (r.x0 <= p.x) && (r.y0 <= p.y)
                 &&(r.x1 > p.x) && (r.y1 > p.y);
    return contains;
}
function B32 intr_contains(I2F32 r, V2F32 p)
{
    B32 contains = (r.x0 <= p.x) && (r.y0 <= p.y)
                 &&(r.x1 > p.x) && (r.y1 > p.y);
    return contains;
}
function B32 intr_contains(I2F64 r, V2F64 p)
{
    B32 contains = (r.x0 <= p.x) && (r.y0 <= p.y)
                 &&(r.x1 > p.x) && (r.y1 > p.y);
    return contains;
}

// interval dimensions
function U64 intr_dimensions(I1U64 r)
{
    U64 dim = r.max - r.min;
    return dim;
}
function S32 intr_dimensions(I1S32 r)
{
    S32 dim = r.max-  r.min;
    return dim;
}
function F32 intr_dimensions(I1F32 r)
{
    F32 dim = r.max - r.min;
    return dim;
}
function F64 intr_dimensions(I1F64 r)
{
    F64 dim = r.max - r.min;
    return dim;
}

function V2S32 intr_dimensions(I2S32 r)
{
    V2S32 dim = r.max - r.min;
    return dim;
}
function V2F32 intr_dimensions(I2F32 r)
{
    V2F32 dim = r.max - r.min;
    return dim;
}
function V2F64 intr_dimensions(I2F64 r)
{
    V2F64 dim = r.max - r.min;
    return dim;
}

// interval center
function F32 intr_center(I1F32 r)
{
    F32 center = (r.min + r.max)*.5f;
    return center;
}
function F64 intr_center(I1F64 r)
{
    F64 center = (r.min + r.max)*.5;
    return center;
}

function V2F32 intr_center(I2F32 r)
{
    V2F32 center = (r.min + r.max)*.5f;
    return center;
}
function V2F64 intr_center(I2F64 r)
{
    V2F64 center = (r.min + r.max)*.5;
    return center;
}

// interval axis
function I1F32 intr_axis(I2F32 r, Axis axis)
{
    I1F32 result = I1F32{
        r.p[0].v[axis],
        r.p[1].v[axis]
    };
    return result;
}
function I1F64 intr_axis(I2F64 r, Axis axis)
{
    I1F64 result = I1F64{
        r.p[0].v[axis],
        r.p[1].v[axis]
    };
    return result;
}