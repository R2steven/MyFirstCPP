#ifndef BASE_H
# define BASE_H

//////////////////////////////////
//  NOTE: Debugging Switches

#define ENABLE_ASSERT 0


//////////////////////////////////
//  NOTE: Context Cracking

#if defined(__clang__)
# define COMPILER_CLANG 1

# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error Missing OS Detection
# endif

# if defined(__amd64__)
#  define ARCH_X64 1
# elif defined(__i386__)
#  define ARCH_X86 1
# elif defined(__arm__)
#  define ARCH_ARM 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# else
#  error Missing ARCH detection
# endif


#elif defined(_MSC_VER)
# define COMPILER_CL 1

# if defined(_WIN32)
#  define OS_WINDOWS 1
# else
#  error Missing OS Detection
# endif

# if defined(_M_AMD64)
#  define ARCH_X64 1
# elif defined(_M_IX86)
#  define ARCH_X86 1
# elif defined(_M_ARM)
#  define ARCH_ARM 1 //TODO(RYAN): Is this x64?
# else
#  error Missing ARCH detection
# endif


#elif defined(__GNUC__)
# define COMPILER_GCC 1

# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error Missing OS Detection
# endif

# if defined(__amd64__)
#  define ARCH_X64 1
# elif defined(__i386__)
#  define ARCH_X86 1
# elif defined(__arm__)
#  define ARCH_ARM 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# else
#  error Missing ARCH detection
# endif

#else
# error no context cracking for this compiler
#endif


#if !defined(COMPILER_CLANG)
# define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_CL)
# define COMPILER_CL 0
#endif
#if !defined(COMPILER_GCC)
# define COMPILER_GCC 0
#endif
#if !defined(OS_WINDOWS)
# define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
# define OS_LINUX 0
#endif
#if !defined(OS_MAC)
# define OS_MAC 0
#endif
#if !defined(ARCH_X64)
# define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
# define ARCH_X86 0
#endif
#if !defined(ARCH_ARM)
# define ARCH_ARM 0
#endif
#if !defined(ARCH_ARM64)
# define ARCH_ARM64 0
#endif

//////////////////////////////////
//  NOTE: Helper Macros

#define Stmnt(S) do{S}while(0)

#if !defined(AssertBreak)
# define AssertBreak() (*(int*)0 = 0)
#endif

#if ENABLE_ASSERT
# define Assert(c) Stmnt(if (!(c)){AssertBreak(); } )
#else
# define Assert(c)
#endif

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#define ArrayCount(a) (sizeof(a)/sizeof(*(a)))

//NOTE different compiler/warning combos may have issue with this, define as you find cases
#define IntFromPtr(p) (U64)((U8*)p-(U8*)0)
#define PtrFromInt(n) (void*)((U8*)0 + (n))

//NOTE Member only accesses abstract strut, offset may not be up to C++ standard
#define Member(T,m) (((T*)0)->m)
#define OffsetOfMember(T,m) IntFromPtr(&Member(T,m))

#define Min(a,b) (((a)<(b))?(a):(b))
#define Max(a,b) (((a)>(b))?(a):(b))
#define Clamp(a,x,b) (((x)<(a))?(a):\
                        ((b)<(x))?(b):\
                            (x))

#define global static
#define local static
#define function static

#define c_linkage_begin extern "C"{
#define c_linkage_end }
#define c_linkage extern "C"

#include <string.h>
#define MemoryZero(p,z) memset((p),0,(z))
#define MemoryZeroStrut(p) MemoryZero(p,sizeof(*(p)))
#define MemoryZeroArray(p) MemoryZero(p,sizeof(p))
#define MemoryZeroTyped(p,c) MemoryZero(p,sizeof(*(p))*(c))

#define MemoryMatch(a,b,z) (memcmp((a),(b),(z)) == 0)

#define MemoryCopy(d,s,z) memmove((d), (s), (z))
#define MemoryCopyStrut(d,s) MemoryCopy((d),(s),\
                                Min(sizeof(*(d)),sizeof(*(s))))
#define MemoryCopyArray(d,s) MemoryCopy((d),(s),\
                                Min(sizeof(s),sizeof(d)))
#define MemoryCopyTyped(d,s,c) MemoryCopy((d),(s),\
                                Min(sizeof(*(d)),sizeof(*(s)))*(c))

//////////////////////////////////
// Note: Linked List Macros

#define DLLPushBack_NP(f,l,n,next,prev)   ((f) == 0?\
                                            ((f) = (l) = (n), (n)->next = (n)->prev = 0)\
                                           :((l)->next = (n), (n)->prev = (l), (l) = (n))\
                                           ,((n)->next = (n->prev = 0)))
#define DLLPushBack(f,l,n) DLLPushBack_NP(f,l,n,next,prev)

#define DLLPushFront(f,l,n,next,prev) DLLPushFront(f,l,n,prev,next)
#define DLLPushFront(f,l,n) DLLPushFront(f,l,n,next,prev)

#define DLLRemove_NP(f,l,n,next,prev)   ((f) == (n)?\
                                          ((f) == (f)->next, (f)->prev = 0)\
                                         :(l) == (n)?\
                                          ((l) = (l)->prev , (l)->next = 0)\
                                         :(((n)->next->prev = (n)->prev),\
                                          ((n)->prev->next = (n)->next)))

#define SLLQueuePush_N(f,l,n,next) ((f) == 0?\
                              (f) = (l) = (n)\
                             :((l)->next = (n),(l) = (n)),\
                              (n)->next = 0)
#define SLLQueuePush(f,l,n) SLLQueuePush_N(f,l,n,next)

#define SLLQueuePushFront(f,l,n,next)   ((f) == 0?\
                                          ((f) = (l) = (n), (n)->next = 0)\
                                         :(n)-next = (f), (f) = (n))

#define SLLQueuePop_N(f,l,next)    ((f)==(l)?\
                              (f) = (l) = 0\
                             :(f)=(f)->next)
#define SLLQueuePop(f,l) SLLQueuePop_N(f,l,next)

#define SLLStackPush_N(f,n,next) ((n)->next = (f), (f) = (n))
#define SLLStackPush(f,n)

#define SLLStackPop_N(f,next) ((f) == 0? 0 : (f) = (f)->next)
#define SLLStackPop(f) SLLStackPop_N(f,next)


//////////////////////////////////
// Note: Basic Types

#include <stdint.h>
typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef S8 B8;
typedef S16 B16;
typedef S32 B32;
typedef S64 B64;
typedef float F32;
typedef double F64;

typedef void VoidFunc(void);

//////////////////////////////////
// Note: Basic Constants

global S8 min_S8 = (S8) 0x80;
global S16 min_S16 = (S16) 0x8000;
global S32 min_S32 = (S32) 0x80000000;
global S64 min_S64 = (S64) 0x8000000000000000llu;

global S8 max_S8 = (S8) 0x7f;
global S16 max_S16 = (S16) 0x7fff;
global S32 max_S32 = (S32) 0x7fffffff;
global S64 max_S64 = (S64) 0x7fffffffffffffffllu;

global S8 max_U8 = 0xff;
global U16 max_U16 = 0xffff;
global U32 max_U32 = 0xffffffff;
global U64 max_U64 = 0xffffffffffffffffllu;

global F32 machine_epsilon_F32 = 1.1920929e-7f;
global F32 pi_F32 = 3.14159265359f;
global F32 tau_F32 = 6.28318530718f;
global F32 e_32 = 2.718281828459045f;
global F32 gold_big_F32 = 1.61803398875f;
global F32 gold_small_F32 = 0.61803398875f;

global F64 machine_epsilon_F64 = 2.220446e-16;
global F64 pi_F64 = 3.14159265359;
global F64 tau_F64 = 6.28318530718;
global F64 e_F64 = 2.718281828459045;
global F64 gold_big_F64 = 1.61803398875;
global F64 gold_small_F64 = 0.61803398875;

//////////////////////////////////
// Note: Symbolic Constants

enum Axis
{
    Axis_X,
    Axis_Y,
    Axis_Z,
    Axis_W
};

enum Side
{
    Side_Min,
    Side_Max
};

enum OperatingSystem
{
    OperatingSystem_Null,
    OperatingSystem_Windows,
    OperatingSystem_Linux,
    OperatingSystem_Mac,
    OperatingSystem_COUNT
};

enum Architecture
{
    Architecture_Null,
    Architecture_X64,
    Architecture_X86,
    Architecture_ARM,
    Architecture_ARM64,
    Architecture_COUNT
};

enum Month {
    Month_Jan,
    Month_Feb,
    Month_Mar,
    Month_Apr,
    Month_May,
    Month_Jun,
    Month_Jul,
    Month_Aug,
    Month_Sep,
    Month_Oct,
    Month_Nov,
    Month_Dec
};

enum DayOfWeek {
    DayOfWeek_Sunday,
    DayOfWeek_Monday,
    DayOfWeek_Tuesday,
    DayOfWeek_Wednesday,
    DayOfWeek_Thursday,
    DayOfWeek_Friday,
    DayOfWeek_Saturday
};

//////////////////////////////////
// Note: Compound Types

union V2S32
{
    struct 
    {
        S32 x;
        S32 y;    
    };
    S32 v[2];
};

union V2F32
{
    struct 
    {
        F32 x;
        F32 y;    
    };
    F32 v[2];
};

union V3F32
{
    struct 
    {
        F32 x;
        F32 y;
        F32 z;    
    };
    F32 v[3];
};

union V4F32
{
    struct 
    {
        F32 x;
        F32 y;
        F32 z;
        F32 w;    
    };
    F32 v[4];
};

union V2F64
{
    struct 
    {
        F64 x;
        F64 y;    
    };
    F64 v[2];
};

union V3F64
{
    struct 
    {
        F64 x;
        F64 y;
        F64 z;    
    };
    F64 v[3];
};

union V4F64
{
    struct 
    {
        F64 x;
        F64 y;
        F64 z;
        F64 w;    
    };
    F64 v[4];
};

union I1F32
{
    struct 
    {
        F32 min;
        F32 max;
    };
    F32 v[2];
};

union I1F64
{
    struct 
    {
        F64 min;
        F64 max;
    };
    F64 v[2];
};

union I1S32
{
    struct 
    {
        S32 min;
        S32 max;
    };
    S32 v[2];
};

union I1U64
{
    struct
    {
        U64 min;
        U64 max;
    };
    struct 
    {
        U64 first;
        U64 opl;
    };
    U64 v[2]; 
};

union I2S32
{
    struct
    {
        V2S32 min;
        V2S32 max;
    };
    struct
    {
        V2S32 p0;
        V2S32 p1;
    };
    struct 
    {
        S32 x0;
        S32 y0;
        S32 x1;
        S32 y1;
    };
    V2S32 p[2];
    S32 v[4];
};

union I2F32
{
    struct
    {
        V2F32 min;
        V2F32 max;
    };
    struct
    {
        V2F32 p0;
        V2F32 p1;
    };
    struct 
    {
        F32 x0;
        F32 y0;
        F32 x1;
        F32 y1;
    };
    V2F32 p[2];
    F32 v[4];
};

union I2F64
{
    struct
    {
        V2F64 min;
        V2F64 max;
    };
    struct
    {
        V2F64 p0;
        V2F64 p1;
    };
    struct 
    {
        F64 x0;
        F64 y0;
        F64 x1;
        F64 y1;
    };
    V2F64 p[2];
    F64 v[4];
};

//////////////////////////////////
// Note: Symbolic Constant Functions

function OperatingSystem operating_system_from_context(void);
function Architecture architexture_from_context(void);

function char* string_from_operating_system(OperatingSystem os);
function char* string_from_architecture(Architecture arch);
function char* string_from_month(Month month);
function char* string_from_day_of_week(DayOfWeek day_of_week);

//////////////////////////////////
// Note: Float Constant Functions

function F32 inf_F32(void);
function F32 neg_inf_F32(void);
function F64 inf_F64(void);
function F64 neg_inf_F64(void);

//////////////////////////////////
// Note: Math Functions

function F32 abs_F32(F32 x);
function F64 abs_F64(F64 x);

function F32 sqrt_F32(F32 x);
function F32 sin_F32(F32 x);
function F32 cos_F32(F32 x);
function F32 tan_F32(F32 x);
function F32 ln_F32(F32 x);

function F64 sqrt_F64(F64 x);
function F64 sin_F64(F64 x);
function F64 cos_F64(F64 x);
function F64 tan_F64(F64 x);
function F64 ln_F64(F64 x);

function F32 lerp_F32(F32 a, F32 b, F32 dx);
function F32 unLerp_F32(F32 a, F32 b, F32 dx);

function F64 lerp_F64(F64 a, F64 b, F64 dx);
function F64 unLerp_F64(F64 a, F64 b, F64 x);

//////////////////////////////////
// Note: Compound Type functions

// constructors
function V2S32 v2s32(S32 x, S32 y);

function V2F32 v2F32(F32 x, F32 y);
function V3F32 v3F32(F32 x, F32 y, F32 z);
function V4F32 v4F32(F32 x, F32 y, F32 z, F32 w);

function V2F64 v2F64(F64 x, F64 y);
function V3F64 v3F64(F64 x, F64 y, F64 z);
function V4F64 v4F64(F64 x, F64 y, F64 z, F64 w);

function I1U64 i1U64(U64 min, U64 max);
function I1S32 i1S32(S32 min, S32 max);
function I1F32 i1F32(F32 min, F32 max);
function I1F64 i1F64(F64 min, F64 max);

function I2S32 i2S32(S32 x0, S32 y0, S32 x1, S32 y1);
function I2S32 i2S32_range(I1S32 min, I1S32 max);
function I2S32 i2S32_vec(V2S32 p0, V2S32 p1);

function I2F32 i2F32(F32 x0, F32 y0, F32 x1, F32 y1);
function I2F32 i2F32_range(I1F32 min, I1F32 max);
function I2F32 i2F32_vec(V2F32 p0, V2F32 p1);

function I2F64 i2F64(F64 x0, F64 y0, F64 x1, F64 y1);
function I2F64 i2F64_range(I1F64 min, I1F64 max);
function I2F64 i2F64_vec(V2F64 p0, V2F64 p1);

// vector addition operations
function V2S32 operator+(const V2S32 &a, const V2S32 &b);

function V2F32 operator+(const V2F32 &a, const V2F32 &b);
function V3F32 operator+(const V3F32 &a, const V3F32 &b);
function V4F32 operator+(const V4F32 &a, const V4F32 &b);

function V2F64 operator+(const V2F64 &a, const V2F64 &b);
function V3F64 operator+(const V3F64 &a, const V3F64 &b);
function V4F64 operator+(const V4F64 &a, const V4F64 &b);

// vector subtraction operations
function V2S32 operator-(const V2S32 &a, const V2S32 &b);

function V2F32 operator-(const V2F32 &a, const V2F32 &b);
function V3F32 operator-(const V3F32 &a, const V3F32 &b);
function V4F32 operator-(const V4F32 &a, const V4F32 &b);

function V2F64 operator-(const V2F64 &a, const V2F64 &b);
function V3F64 operator-(const V3F64 &a, const V3F64 &b);
function V4F64 operator-(const V4F64 &a, const V4F64 &b);

// vector multiplication operations
function V2S32 operator*(const V2S32 &a, const S32 &b);

function V2F32 operator*(const V2F32 &a, const F32 &b);
function V3F32 operator*(const V3F32 &a, const F32 &b);
function V4F32 operator*(const V4F32 &a, const F32 &b);

function V2F64 operator*(const V2F64 &a, const F64 &b);
function V3F64 operator*(const V3F64 &a, const F64 &b);
function V4F64 operator*(const V4F64 &a, const F64 &b);

// vector dot operations
function F32 vec_dot(V2F32 a, V2F32 b);
function F32 vec_dot(V3F32 a, V3F32 b);
function F32 vec_dot(V4F32 a, V4F32 b);

function F64 vec_dot(V2F64 a, V2F64 b);
function F64 vec_dot(V3F64 a, V3F64 b);
function F64 vec_dot(V4F64 a, V4F64 b);

// vector cross operations
function F32 vec_cross_2D(V2F32 a, V2F32 b);
function V2F32 naive_2D_cross(V2F32 a, V2F32 b);
function V3F32 vec_cross(V3F32 a, V3F32 b);
function V4F32 vec_cross(V4F32 a, V4F32 b);

function F64 vec_cross_2D(V2F64 a, V2F64 b);
function V2F64 naive_2D_cross(V2F64 a, V2F64 b);
function V3F64 vec_cross(V3F64 a, V3F64 b);
function V4F64 vec_cross(V4F64 a, V4F64 b);

// hadamard (naieve matrix multiplication) operations
function V2S32 vec_hadamard(V2S32 a, V2S32 b);

function V2F32 vec_hadamard(V2F32 a, V2F32 b);
function V3F32 vec_hadamard(V3F32 a, V3F32 b);
function V4F32 vec_hadamard(V4F32 a, V4F32 b);

function V2F64 vec_hadamard(V2F64 a, V2F64 b);
function V3F64 vec_hadamard(V3F64 a, V3F64 b);
function V4F64 vec_hadamard(V4F64 a, V4F64 b);

// interval overlaps
function B32 intr_overlaps(I1U64 a, I1U64 b);
function B32 intr_overlaps(I1S32 a, I1S32 b);
function B32 intr_overlaps(I1F32 a, I1F32 b);
function B32 intr_overlaps(I1F64 a, I1F64 b);

function B32 intr_overlaps(I2S32 a, I2S32 b);
function B32 intr_overlaps(I2F32 a, I2F32 b);
function B32 intr_overlaps(I2F64 a, I2F64 b);

// interval contains
function B32 intr_contains(I1U64 r, U64 p);
function B32 intr_contains(I1S32 r, S32 p);
function B32 intr_contains(I1F32 r, F32 p);
function B32 intr_contains(I1F64 r, F64 p);

function B32 intr_contains(I2S32 r, S32 p);
function B32 intr_contains(I2F32 r, F32 p);
function B32 intr_contains(I2F64 r, F64 p);

// interval dimensions
function U64 intr_dimensions(I1U64 r);
function S32 intr_dimensions(I1S32 r);
function F32 intr_dimensions(I1F32 r);
function F64 intr_dimensions(I1F64 r);

function V2S32 intr_dimensions(I2S32 r);
function V2F32 intr_dimensions(I2F32 r);
function V2F64 intr_dimensions(I2F64 r);

// interval center
function F32 intr_center(I1F32 r);
function F64 intr_center(I1F64 r);

function V2F32 intr_center(I2F32 r);
function V2F64 intr_center(I2F64 r);

// interval axis
function I1F32 intr_axis(I2F32 r, Axis axis);
function I1F32 intr_axis(I2F32 r, Axis axis);

#endif //Base_H