/*****************************************************************************
 * ArbInt.hxx
 *****************************************************************************
 * Arbitrary integer number class.
 *****************************************************************************/

// Include guard.
#if !defined(ARBINT_7b2y3kb789f2u3du)
  #define ARBINT_7b2y3kb789f2u3du

// STL includes.
  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include <limits>
  #include <cmath>

// Internal includes.
  #include "SafeInt.hxx"
  #include "ReferencePointer.hxx"
  #include "toString.hxx"
  #include "rppower.hxx"
  #include "Exception.hxx"

// Namespace wrapping.
namespace DAC {
  
  /***************************************************************************
   * ArbInt
   ***************************************************************************
   * This is an integer of an arbitrary number of digits.
   ***************************************************************************/
  class ArbInt {
    
    /*
     * Private members.
     */
    private:
      
      /***********************************************************************/
      // Typedefs.
      
      // Native digit type. Do not change this unless you have a very good
      // reason. This must be an unsigned integer type.
      typedef unsigned int _DigT;
    
    /*
     * Public members.
     */
    public:
      
      /***********************************************************************/
      // Typedefs.
      
      typedef _DigT value_type;
      
      /***********************************************************************/
      // Function members.
      
      // Default constructor.
      ArbInt ();
      
      // Copy constructor.
      ArbInt (ArbInt const& number, bool const copynow = false);
      
      // Conversion constructor.
                         explicit ArbInt (std::string const& number);
      template <class T> explicit ArbInt (T           const  number);
      
      // Increment / decrement operators.
      ArbInt& operator ++ ();
      ArbInt  operator ++ (int);
      ArbInt& operator -- ();
      ArbInt  operator -- (int);
      
      // Unary sign operators.
      ArbInt operator + () const;
      ArbInt operator - () const;
      
      // Not operator.
      bool operator ! () const;
      
      // Bitwise compliment.
      ArbInt operator ~ () const;
      
      // Casting operators.
      operator bool               () const;
      operator signed   char      () const;
      operator unsigned char      () const;
      operator signed   short int () const;
      operator unsigned short int () const;
      operator signed   int       () const;
      operator unsigned int       () const;
      operator signed   long int  () const;
      operator unsigned long int  () const;
      
      // Assignment operator.
                         ArbInt& operator = (ArbInt      const& number);
                         ArbInt& operator = (std::string const& number);
      template <class T> ArbInt& operator = (T           const  number);
      
      // Arithmetic assignment operators.
                         ArbInt& operator *= (ArbInt const& number);
      template <class T> ArbInt& operator *= (T      const  number);
                         ArbInt& operator /= (ArbInt const& number);
      template <class T> ArbInt& operator /= (T      const  number);
                         ArbInt& operator %= (ArbInt const& number);
      template <class T> ArbInt& operator %= (T      const  number);
                         ArbInt& operator += (ArbInt const& number);
      template <class T> ArbInt& operator += (T      const  number);
                         ArbInt& operator -= (ArbInt const& number);
      template <class T> ArbInt& operator -= (T      const  number);
      
      // Bit shift assignment operators.
                         ArbInt& operator <<= (ArbInt const& number);
      template <class T> ArbInt& operator <<= (T      const  number);
                         ArbInt& operator >>= (ArbInt const& number);
      template <class T> ArbInt& operator >>= (T      const  number);
      
      // Bitwise assignment operators.
                         ArbInt& operator &= (ArbInt const& number);
      template <class T> ArbInt& operator &= (T      const  number);
                         ArbInt& operator |= (ArbInt const& number);
      template <class T> ArbInt& operator |= (T      const  number);
                         ArbInt& operator ^= (ArbInt const& number);
      template <class T> ArbInt& operator ^= (T      const  number);
      
      // Accessors.
                         value_type Base  () const;
      template <class T> T          Value () const;
                         ArbInt& Base  (value_type const base);
      template <class T> ArbInt& Value (T          const number);
      
      // Reset to just-constructed state.
      ArbInt& clear ();
      
      // Copy another number.
      ArbInt& copy (ArbInt const& number, bool const copynow = false);
      
      // Set this number.
                         ArbInt& set (ArbInt      const& number);
                         ArbInt& set (std::string const& number);
      template <class T> ArbInt& set (T           const  number);
      
      // Push digits into this number.
                         ArbInt& push_back (ArbInt      const& number);
                         ArbInt& push_back (std::string const& number);
      template <class T> ArbInt& push_back (SafeInt<T>  const  number);
      template <class T> ArbInt& push_back (T           const  number);
      
      // Return a string of this number.
      std::string toString () const;
      
      // Arithmetic operator backends.
                         ArbInt& op_mul (ArbInt const& number);
      template <class T> ArbInt& op_mul (T      const  number);
                         ArbInt& op_div (ArbInt const& number, ArbInt* const remainder = 0);
      template <class T> ArbInt& op_div (T      const  number, ArbInt* const remainder = 0);
                         ArbInt& op_mod (ArbInt const& number);
      template <class T> ArbInt& op_mod (T      const  number);
                         ArbInt& op_add (ArbInt const& number);
      template <class T> ArbInt& op_add (T      const  number);
                         ArbInt& op_sub (ArbInt const& number);
      template <class T> ArbInt& op_sub (T      const  number);
      
      // Bit shift operator backends.
                         ArbInt& op_shl (ArbInt const& number);
      template <class T> ArbInt& op_shl (T      const  number);
                         ArbInt& op_shr (ArbInt const& number);
      template <class T> ArbInt& op_shr (T      const  number);
      
      // Comparison operator backends.
                         bool op_gt (ArbInt const& number) const;
      template <class T> bool op_gt (T      const  number) const;
                         bool op_ge (ArbInt const& number) const;
      template <class T> bool op_ge (T      const  number) const;
                         bool op_lt (ArbInt const& number) const;
      template <class T> bool op_lt (T      const  number) const;
                         bool op_le (ArbInt const& number) const;
      template <class T> bool op_le (T      const  number) const;
                         bool op_eq (ArbInt const& number) const;
      template <class T> bool op_eq (T      const  number) const;
                         bool op_ne (ArbInt const& number) const;
      template <class T> bool op_ne (T      const  number) const;
      
      // Bitwise operator backends.
                         ArbInt& op_bit_and (ArbInt const& number);
      template <class T> ArbInt& op_bit_and (T             number);
                         ArbInt& op_bit_ior (ArbInt const& number);
      template <class T> ArbInt& op_bit_ior (T             number);
                         ArbInt& op_bit_xor (ArbInt const& number);
      template <class T> ArbInt& op_bit_xor (T             number);
                         ArbInt& op_bit_cpm ();
      
      // Return information about this number.
      bool isEven () const;
      bool isZero () const;
      bool isOdd  () const;
      
      // Raise this number to a power.
                         ArbInt pow (ArbInt const& exp);
      template <class T> ArbInt pow (T      const  exp);
      
      // Find a root of this number.
      ArbInt root (ArbInt const& find, ArbInt& divisor, ArbInt& remainder);
      
      /***********************************************************************/
      // Static function members.
      
      // Return the maximum string input base.
      static value_type max_input_base ();
    
    /*
     * Private members.
     */
    private:
      
      /***********************************************************************/
      // Typedefs.
      
      typedef char          _StrChrT; // String character.
      typedef unsigned char _NumChrT; // Numeric character.
      
      typedef std::vector<_NumChrT> _DigStrT; // String of character
                                              // digits.
      typedef std::vector<_DigT>    _DigsT;   // String of native
                                              // digits.
      
      typedef ReferencePointer<_DigsT> _DataPT; // Pointer to data.
      
      /***********************************************************************/
      // Data types.
      
      // Directions.
      enum _Dir { _DIR_L, _DIR_R };
      
      // Number types.
      enum _NumType { _NUM_UINT, _NUM_SINT, _NUM_FLPT };
      
      // Determine number type.
      template <class T> class _GetNumType { public: static _NumType const value; };
      
      // Set.
      template <class T, _NumType> class _Set;
      template <class T> class _Set<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Set<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Set<T, _NUM_FLPT> { public:                                                 static void op (ArbInt& l, T const r); };
      
      // Multiply.
      template <class T, _NumType> class _Mul;
      template <class T> class _Mul<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Mul<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Mul<T, _NUM_FLPT> { public:                                                 static void op (ArbInt& l, T const r); };
      
      // Divide.
      template <class T, _NumType> class _Div;
      template <class T> class _Div<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> r, ArbInt* remainder = 0); static void op (ArbInt& l, T const r, ArbInt* const remainder = 0); };
      template <class T> class _Div<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> r, ArbInt* remainder = 0); static void op (ArbInt& l, T const r, ArbInt* const remainder = 0); };
      template <class T> class _Div<T, _NUM_FLPT> { public:                                                                  static void op (ArbInt& l, T const r, ArbInt* const remainder = 0); };
      
      // Modulo divide.
      template <class T, _NumType> class _Mod;
      template <class T> class _Mod<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Mod<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Mod<T, _NUM_FLPT> { public:                                                 static void op (ArbInt& l, T const r); };
      
      // Add.
      template <class T, _NumType> class _Add;
      template <class T> class _Add<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Add<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Add<T, _NUM_FLPT> { public:                                                 static void op (ArbInt& l, T const r); };
      
      // Subtract.
      template <class T, _NumType> class _Sub;
      template <class T> class _Sub<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Sub<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Sub<T, _NUM_FLPT> { public:                                                 static void op (ArbInt& l, T const r); };
      
      // Shift left.
      template <class T, _NumType> class _ShL;
      template <class T> class _ShL<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShL<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShL<T, _NUM_FLPT> { public:                                                 static void op (ArbInt& l, T const r); };
      
      // Shift right.
      template <class T, _NumType> class _ShR;
      template <class T> class _ShR<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShR<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShR<T, _NUM_FLPT> { public:                                                 static void op (ArbInt& l, T const r); };
      
      // Greater than.
      template <class T, _NumType> class _GT;
      template <class T> class _GT<T, _NUM_UINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _GT<T, _NUM_SINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _GT<T, _NUM_FLPT> { public:                                                 static void op (ArbInt const& l, T r); };
      
      // Greater than or equal to.
      template <class T, _NumType> class _GE;
      template <class T> class _GE<T, _NUM_UINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _GE<T, _NUM_SINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _GE<T, _NUM_FLPT> { public:                                                 static void op (ArbInt const& l, T r); };
      
      // Less than.
      template <class T, _NumType> class _LT;
      template <class T> class _LT<T, _NUM_UINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _LT<T, _NUM_SINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _LT<T, _NUM_FLPT> { public:                                                 static void op (ArbInt const& l, T r); };
      
      // Less than or equal to.
      template <class T, _NumType> class _LE;
      template <class T> class _LE<T, _NUM_UINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _LE<T, _NUM_SINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _LE<T, _NUM_FLPT> { public:                                                 static void op (ArbInt const& l, T r); };
      
      // Equal to.
      template <class T, _NumType> class _EQ;
      template <class T> class _EQ<T, _NUM_UINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _EQ<T, _NUM_SINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _EQ<T, _NUM_FLPT> { public:                                                 static void op (ArbInt const& l, T r); };
      
      // Not equal to.
      template <class T, _NumType> class _NE;
      template <class T> class _NE<T, _NUM_UINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _NE<T, _NUM_SINT> { public: static void op (ArbInt const& l, SafeInt<T> r); static void op (ArbInt const& l, T r); };
      template <class T> class _NE<T, _NUM_FLPT> { public:                                                 static void op (ArbInt const& l, T r); };
      
      // Bitwise AND.
      template <class T, _NumType> class _Bit_AND;
      template <class T> class _Bit_AND<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Bit_AND<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      
      // Bitwise inclusive OR.
      template <class T, _NumType> class _Bit_IOR;
      template <class T> class _Bit_IOR<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Bit_IOR<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      
      // Bitwise exclusive OR.
      template <class T, _NumType> class _Bit_XOR;
      template <class T> class _Bit_XOR<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      template <class T> class _Bit_XOR<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const r); static void op (ArbInt& l, T const r); };
      
      /***********************************************************************/
      // Data members.
      
      // The number.
      _DataPT _digits;
      
      // The default base of this number.
      _DigT _base;
      
      /***********************************************************************/
      // Static data members.
      
      static bool s_initialized;
      
      static int   s_digitbits; // Number of bits in a digit.
      static _DigT s_digitbase; // Base of native digits.
      static _DigT s_bitmask;   // Bitmask of digits.
      
      static _NumChrT s_numodigits; // Number of output digits.
      static _StrChrT s_odigits[];  // Output digits.
      
      static _NumChrT              s_numidigits; // Number of input digits.
      static std::vector<_NumChrT> s_idigits;    // Input digits.
      
      /***********************************************************************/
      // Function members.
      
      // Common initialization tasks.
      void _init ();
      
      // Perform carry or borrow.
      ArbInt& _carry  (_DigsT::size_type start);
      ArbInt& _borrow (_DigsT::size_type start);
      
      // Trim insignificant zeros.
      ArbInt& _trimZeros ();
      
      // Bit shift this number.
      ArbInt& _shift (ArbInt const& bits, _Dir direction);
      
      /***********************************************************************/
      // Static function members.
      
      // Class initialization.
      static void s_classInit ();
      
      // Trim zeros from a given container.
      template <class T> static void s_trimZerosB (T& c);
      template <class T> static void s_trimZerosE (T& c);
      template <class T> static void s_trimZeros  (T& c);
      
      // Do long division on a given container. Returns the remainder.
      template <class DivndT, class DivorT> static DivorT s_longDiv (DivndT& divnd, DivorT divor, value_type base);
      
      // Convert a container from one base to another.
      template <class FT, class TT> static void s_baseConv (FT const& from, value_type frombase, TT& to, value_type tobase);
      
      // Validate a base.
      static void s_validateBase (value_type base);
    
  };
  
  /***************************************************************************
   * Errors.
   ***************************************************************************/
  namespace ArbIntErrors {
    
    // All ArbInt errors are based off of this.
    class Base : public Exception {
      public:
        virtual char const* what () const throw();
        virtual ~Base () throw();
    };
    
    // Bad format.
    class BadFormat : public Base {
      public:
        virtual char const* what () const throw();
        BadFormat& Problem  (char const*                               problem)  throw();
        BadFormat& Position (std::string::size_type                    position) throw();
        BadFormat& Number   (ConstReferencePointer<std::string> const& number)   throw();
        char const* Problem                       () const throw();
        std::string::size_type Position           () const throw();
        ConstReferencePointer<std::string> Number () const throw();
      private:
        char const*                        _problem;
        std::string::size_type             _position;
        ConstReferencePointer<std::string> _number;
    };
    
    // Attempt to set ArbInt to a negative number.
    class Negative : public Base {
      public:
        virtual char const* what () const throw();
    };
    template <class T> class NegativeSet : public Negative {
      public:
        virtual char const* what () const throw();
        NegativeSet& Source (T const source) throw();
        T Source () const throw();
      private:
        T _source;
    };
    class NegativeUnary : public Negative {
      public:
        virtual char const* what () const throw();
        NegativeUnary& Number   (ArbInt      const& number) throw();
        NegativeUnary& Operator (char const*        op)     throw();
        NegativeUnary& Prefix   (bool               prefix) throw();
        ArbInt      Number   () const throw();
        char const* Operator () const throw();
        bool        Prefix   () const throw();
      private:
        ArbInt      _number;
        char const* _op;
        bool        _prefix;
    };
    template <class T, class U> class NegativeBinary : public Negative {
      public:
        virtual char const* what () const throw();
        NegativeBinary& Left     (T           l)  throw();
        NegativeBinary& Operator (char const* op) throw();
        NegativeBinary& Right    (U           r)  throw();
        T           Left     () const throw();
        char const* Operator () const throw();
        U           Right    () const throw();
      private:
        T           _l;
        char const* _op;
        U           _r;
    };
    
    // Operation overruns container size. Generic version first for easy
    // catching, then specialized version based off that.
    class Overrun : public Base {
      public:
        virtual char const* what () const throw();
    };
    template <class T> class OverrunSpecialized : public Overrun {
      public:
        virtual char const* what () const throw();
        OverrunSpecialized& Problem (char const* problem) throw();
        OverrunSpecialized& Offset  (T           offset)  throw();
        OverrunSpecialized& Limit   (T           limit)   throw();
        char const* Problem () const throw();
        T           Offset  () const throw();
        T           Limit   () const throw();
      private:
        char const* _problem;
        T           _offset;
        T           _limit;
    };
    
    // Divide by zero.
    class DivByZero : public Base {
      public:
        virtual char const* what () const throw();
    };
    template <class T, class U> class DivByZeroBinary : public DivByZero {
      public:
        virtual char const* what () const throw();
        DivByZeroBinary& Left     (T           l)  throw();
        DivByZeroBinary& Operator (char const* op) throw();
        DivByZeroBinary& Right    (U           r)  throw();
        T           Left     () const throw();
        char const* Operator () const throw();
        U           Right    () const throw();
      private:
        T           _l;
        char const* _op;
        U           _r;
    };
    
    // Overflow converting to a scalar type.
    class ScalarOverflow : public Base {
      public:
        virtual char const* what () const throw();
    };
    template <class T> class ScalarOverflowSpecialized : public ScalarOverflow {
      public:
        virtual char const* what () const throw();
        ScalarOverflowSpecialized& Number (ArbInt const& number) throw();
        ScalarOverflowSpecialized& Limit  (T             limit)  throw();
        ArbInt Number () const throw();
        T      Limit  () const throw();
      private:
        ArbInt _number;
        T      _limit;
    };
    
    // Requested base is out of range.
    class BaseOutOfRange : public Base {
      public:
        virtual char const* what () const throw();
    };
    template <class T, class U> class BaseOutOfRangeSpecialized : public BaseOutOfRange {
      public:
        virtual char const* what () const throw();
        BaseOutOfRangeSpecialized& Base  (T base)  throw();
        BaseOutOfRangeSpecialized& Limit (U limit) throw();
        T Base  () const throw();
        U Limit () const throw();
      private:
        T _base;
        U _limit;
    };
    template <class T, class U> class BaseOutOfRangeMin : public BaseOutOfRangeSpecialized<T, U> {
      public:
        virtual char const* what () const throw();
    };
    template <class T, class U> class BaseOutOfRangeMax : public BaseOutOfRangeSpecialized<T, U> {
      public:
        virtual char const* what () const throw();
    };
    
    // Requested root is too large to calculate.
    class RootTooLarge : public Base {
      public:
        virtual char const* what () const throw();
        RootTooLarge& Number (ArbInt const& number) throw();
        RootTooLarge& Root   (ArbInt const& root)   throw();
        ArbInt Number () const throw();
        ArbInt Root   () const throw();
      private:
        ArbInt _number;
        ArbInt _root;
    };
    
  }
  
  /***************************************************************************
   * Operators.
   ***************************************************************************/
  
  // Stream I/O operators.
  std::ostream&       operator << (std::ostream&       l, ArbInt const& r);
  std::ostringstream& operator << (std::ostringstream& l, ArbInt const& r);
  std::istream&       operator >> (std::istream&       l, ArbInt&       r);
  
  // Arithmetic operators.
                     ArbInt operator * (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator * (ArbInt const& l, T             r);
  template <class T> ArbInt operator * (T             l, ArbInt const& r);
                     ArbInt operator / (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator / (ArbInt const& l, T             r);
  template <class T> ArbInt operator / (T             l, ArbInt const& r);
                     ArbInt operator % (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator % (ArbInt const& l, T             r);
  template <class T> ArbInt operator % (T             l, ArbInt const& r);
                     ArbInt operator + (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator + (ArbInt const& l, T             r);
  template <class T> ArbInt operator + (T             l, ArbInt const& r);
                     ArbInt operator - (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator - (ArbInt const& l, T             r);
  template <class T> ArbInt operator - (T             l, ArbInt const& r);
  
  // Bit shift operators.
                     ArbInt operator << (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator << (ArbInt const& l, T             r);
  template <class T> ArbInt operator << (T             l, ArbInt const& r);
                     ArbInt operator >> (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator >> (ArbInt const& l, T             r);
  template <class T> ArbInt operator >> (T             l, ArbInt const& r);
  
  // Comparsion operators.
                     bool operator >  (ArbInt const& l, ArbInt const& r);
  template <class T> bool operator >  (ArbInt const& l, T             r);
  template <class T> bool operator >  (T             l, ArbInt const& r);
                     bool operator >= (ArbInt const& l, ArbInt const& r);
  template <class T> bool operator >= (ArbInt const& l, T             r);
  template <class T> bool operator >= (T             l, ArbInt const& r);
                     bool operator <  (ArbInt const& l, ArbInt const& r);
  template <class T> bool operator <  (ArbInt const& l, T             r);
  template <class T> bool operator <  (T             l, ArbInt const& r);
                     bool operator <= (ArbInt const& l, ArbInt const& r);
  template <class T> bool operator <= (ArbInt const& l, T             r);
  template <class T> bool operator <= (T             l, ArbInt const& r);
                     bool operator == (ArbInt const& l, ArbInt const& r);
  template <class T> bool operator == (ArbInt const& l, T             r);
  template <class T> bool operator == (T             l, ArbInt const& r);
                     bool operator != (ArbInt const& l, ArbInt const& r);
  template <class T> bool operator != (ArbInt const& l, T             r);
  template <class T> bool operator != (T             l, ArbInt const& r);
  
  // Bitwise operators.
                     ArbInt operator & (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator & (ArbInt const& l, T             r);
  template <class T> ArbInt operator & (T             l, ArbInt const& r);
                     ArbInt operator | (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator | (ArbInt const& l, T             r);
  template <class T> ArbInt operator | (T             l, ArbInt const& r);
                     ArbInt operator ^ (ArbInt const& l, ArbInt const& r);
  template <class T> ArbInt operator ^ (ArbInt const& l, T             r);
  template <class T> ArbInt operator ^ (T             l, ArbInt const& r);
  
  //FIXME: Implement assignment arithmetic operators.
  
  /***************************************************************************
   * Inline and template definitions.
   ***************************************************************************/

  /***************************************************************************/
  // Function members.
  
  // Conversion constructor.
  template <class T> ArbInt::ArbInt (T number) {
    
    // Call common init.
    _init();
    
    // Set the number.
    set(number);
    
  }
  
  // Increment / decrement operators.
  inline ArbInt& ArbInt::operator ++ ()    { return op_add(1);                               }
  inline ArbInt  ArbInt::operator ++ (int) { ArbInt retval(*this); op_add(1); return retval; }
  inline ArbInt& ArbInt::operator -- ()    {
    try {
      return op_sub(1);
    } catch (ArbIntErrors::NegativeBinary<ArbInt, int>) {
      throw ArbIntErrors::NegativeUnary().Number(*this).Operator("--").Prefix(true);
    }
  }
  inline ArbInt  ArbInt::operator -- (int) {
    ArbInt retval(*this);
    try {
      op_sub(1);
    } catch (ArbIntErrors::NegativeBinary<ArbInt, int>) {
      throw ArbIntErrors::NegativeUnary().Number(*this).Operator("--").Prefix(false);
    }
    return retval;
  }
  
  // Unary sign operators.
  inline ArbInt ArbInt::operator + () const { return *this;                                                                 }
  inline ArbInt ArbInt::operator - () const { throw ArbIntErrors::NegativeUnary().Number(*this).Operator("-").Prefix(true); }
  
  // Bitwise compliment.
  inline ArbInt ArbInt::operator ~ () const { return ArbInt(*this).op_bit_cpm(); }
  
  // Casting operators.
  inline ArbInt::operator bool               () const { return !isZero();                   }
  inline ArbInt::operator signed   char      () const { return Value<signed   char     >(); }
  inline ArbInt::operator unsigned char      () const { return Value<unsigned char     >(); }
  inline ArbInt::operator signed   short int () const { return Value<signed   short int>(); }
  inline ArbInt::operator unsigned short int () const { return Value<unsigned short int>(); }
  inline ArbInt::operator signed   int       () const { return Value<signed   int      >(); }
  inline ArbInt::operator unsigned int       () const { return Value<unsigned int      >(); }
  inline ArbInt::operator signed   long int  () const { return Value<signed   long int >(); }
  inline ArbInt::operator unsigned long int  () const { return Value<unsigned long int >(); }
  
  // Assignment operator.
                     inline ArbInt& ArbInt::operator = (ArbInt      const& number) { return set(number); }
                     inline ArbInt& ArbInt::operator = (std::string const& number) { return set(number); }
  template <class T> inline ArbInt& ArbInt::operator = (T                  number) { return set(number); }
  
  // Arithmetic assignment operators.
                     inline ArbInt& ArbInt::operator *= (ArbInt const& number) { return op_mul(number); }
  template <class T> inline ArbInt& ArbInt::operator *= (T             number) { return op_mul(number); }
                     inline ArbInt& ArbInt::operator /= (ArbInt const& number) { return op_div(number); }
  template <class T> inline ArbInt& ArbInt::operator /= (T             number) { return op_div(number); }
                     inline ArbInt& ArbInt::operator %= (ArbInt const& number) { return op_mod(number); }
  template <class T> inline ArbInt& ArbInt::operator %= (T             number) { return op_mod(number); }
                     inline ArbInt& ArbInt::operator += (ArbInt const& number) { return op_add(number); }
  template <class T> inline ArbInt& ArbInt::operator += (T             number) { return op_add(number); }
                     inline ArbInt& ArbInt::operator -= (ArbInt const& number) { return op_sub(number); }
  template <class T> inline ArbInt& ArbInt::operator -= (T             number) { return op_sub(number); }
  
  // Bit shift assignment operators.
                     inline ArbInt& ArbInt::operator <<= (ArbInt const& number) { return op_shl(number); }
  template <class T> inline ArbInt& ArbInt::operator <<= (T             number) { return op_shl(number); }
                     inline ArbInt& ArbInt::operator >>= (ArbInt const& number) { return op_shr(number); }
  template <class T> inline ArbInt& ArbInt::operator >>= (T             number) { return op_shr(number); }
  
  // Bitwise assignment operators.
                     inline ArbInt& ArbInt::operator &= (ArbInt const& number) { return op_bit_and(number); }
  template <class T> inline ArbInt& ArbInt::operator &= (T             number) { return op_bit_and(number); }
                     inline ArbInt& ArbInt::operator |= (ArbInt const& number) { return op_bit_ior(number); }
  template <class T> inline ArbInt& ArbInt::operator |= (T             number) { return op_bit_ior(number); }
                     inline ArbInt& ArbInt::operator ^= (ArbInt const& number) { return op_bit_xor(number); }
  template <class T> inline ArbInt& ArbInt::operator ^= (T             number) { return op_bit_xor(number); }
  
  // Get the base of this number.
  inline ArbInt::value_type ArbInt::Base () const { return _base; }
  
  // Get the value of this number.
  template <class T> T ArbInt::Value () const {
    SafeInt<T> retval;
    for (typename _DigsT::iterator i = _digits->begin(); i != _digits->end(); ++i) {
      try {
        retval += *i * rppower(SafeInt<_DigT>(s_digitbase), (i - _digits->begin()));
      } catch (SafeIntErrors::Overflow) {
        throw ArbIntErrors::ScalarOverflowSpecialized<T>().Number(*this).Limit(std::numeric_limits<T>::max());
      }
    }
    return retval;
  }
  
  // Set the base of this number.
  inline ArbInt& ArbInt::Base (value_type base) {
    if (base < 2) {
      throw ArbIntErrors::BaseOutOfRangeMin<value_type, _DigT>().Base(base).Limit(2);
    }
    if (base > s_digitbase) {
      throw ArbIntErrors::BaseOutOfRangeMax<value_type, _DigT>().Base(base).Limit(s_digitbase);
    }
    _base = base;
    return *this;
  }
  
  // Set the value of this number.
  template <class T> inline ArbInt& ArbInt::Value (T number) { return set(number); }
  
  // Set this number from another ArbInt.
  inline ArbInt& ArbInt::set (ArbInt const& number) { _digits = number._digits; return *this; }
  
  // Set this number from another number.
  template <class T> inline ArbInt& ArbInt::set (T number) { _Set<T, _GetNumType<T>::value>::op(*this, number); return *this; }
  
  // Push a string onto the back of this number.
                     inline ArbInt& ArbInt::push_back (ArbInt     const& number) { return push_back(ArbInt(number).Base(_base).toString()); }
  template <class T> inline ArbInt& ArbInt::push_back (SafeInt<T>        number) { return push_back(static_cast<T>(number));                }
  template <class T> inline ArbInt& ArbInt::push_back (T                 number) { return push_back(DAC::toString(number));                 }
  
  // Arithmetic operator backends.
  template <class T> inline ArbInt& ArbInt::op_mul (T number)                          { _Mul<T, _GetNumType<T>::value>::op(*this, number);            return *this; }
  template <class T> inline ArbInt& ArbInt::op_div (T number, ArbInt* const remainder) { _Div<T, _GetNumType<T>::value>::op(*this, number, remainder); return *this; }
  template <class T> inline ArbInt& ArbInt::op_mod (T number)                          { _Mod<T, _GetNumType<T>::value>::op(*this, number);            return *this; }
  template <class T> inline ArbInt& ArbInt::op_add (T number)                          { _Add<T, _GetNumType<T>::value>::op(*this, number);            return *this; }
  template <class T> inline ArbInt& ArbInt::op_sub (T number)                          { _Sub<T, _GetNumType<T>::value>::op(*this, number);            return *this; }
  
  // Shift left, shift right.
                     inline ArbInt& ArbInt::op_shl (ArbInt const& number) { ArbInt retval(*this, true); retval._shift(number, _DIR_L); return copy(retval); }
  template <class T> inline ArbInt& ArbInt::op_shl (T             number) { ArbInt retval(*this, true); retval._shift(number, _DIR_L); return copy(retval); }
                     inline ArbInt& ArbInt::op_shr (ArbInt const& number) { ArbInt retval(*this, true); retval._shift(number, _DIR_R); return copy(retval); }
  template <class T> inline ArbInt& ArbInt::op_shr (T             number) { ArbInt retval(*this, true); retval._shift(number, _DIR_R); return copy(retval); }
  
  // Greater than an integral type.
  template <class T> bool ArbInt::op_gt (SafeInt<T> const number) const {
    
    // Always greater than negative numbers.
    if (number < 0) {
      return true;
    }
    
    // If the number is too large to compare directly, resort to conversion
    // to ArbInt then compare.
    if (number >= s_digitbase) {
      
      // RAWR!
      return op_gt(ArbInt(number));
      
    // Otherwise compare directly.
    } else {
      
      // If the container is empty, it cannot be greater than anything but
      // a negative number.
      if (isZero()) {
        return (number < 0);
      }
      
      // If the container is larger than 1, it must be greater.
      if (_digits->size() > 1) {
        return true;
      }
      
      // Compare.
      return ((*(_digits))[0] > number);
      
    }
    
  }
  template <class T> inline bool ArbInt::op_gt (T number) const { return op_gt(SafeInt<T>(number)); }
  
  // Less than an integral type.
  template <class T> bool ArbInt::op_lt (SafeInt<T> number) const {
    
    // Never less than 0.
    if (number <= 0) {
      return false;
    }
    
    // If the number is too large to compare directly, resort to conversion
    // to ArbInt then compare.
    if (number >= s_digitbase) {
      
      // Pong.
      return op_lt(ArbInt(number));
    
    // Otherwise compare directly.  
    } else {
      
      // If the container is empty, it must be less than anything but 0,
      // which was already checked.
      if (isZero()) {
        return true;
      }
      
      // If the container is larger than 1 element, it cannot be less.
      if (_digits->size() > 1) {
        return false;
      }
      
      // Compare.
      return ((*(_digits))[0] < number);
      
    }
    
  }
  template <class T> inline bool ArbInt::op_lt (T number) const { return op_lt(SafeInt<T>(number)); }
  
  // Equal to an integral type.
  template <class T> bool ArbInt::op_eq (SafeInt<T> number) const {
    
    // Never less than 0.
    if (number < 0) {
      return false;
    }
    
    // If the number is too large to compare directly, resort to conversion
    // to ArbInt then compare.
    if (number >= s_digitbase) {
      
      // Horf.
      return op_eq(ArbInt(number));
      
    // Otherwise compare directly.
    } else {
      
      // If the container is empty, it can only equal 0.
      if (isZero()) {
        return (number == 0);
      }
      
      // If the container is larger than 1 element, it cannot be equal.
      if (_digits->size() > 1) {
        return false;
      }
      
      // Compare.
      return ((*(_digits))[0] == number);
      
    }
    
  }
  template <class T> inline bool ArbInt::op_eq (T number) const { return op_eq(SafeInt<T>(number)); }
  
  // Comparison operators.
                     inline bool ArbInt::op_ge (ArbInt     const& number) const { return !op_lt(number); }
  template <class T> inline bool ArbInt::op_ge (SafeInt<T>        number) const { return !op_lt(number); }
  template <class T> inline bool ArbInt::op_ge (T                 number) const { return !op_lt(number); }
                     inline bool ArbInt::op_le (ArbInt     const& number) const { return !op_gt(number); }
  template <class T> inline bool ArbInt::op_le (SafeInt<T>        number) const { return !op_gt(number); }
  template <class T> inline bool ArbInt::op_le (T                 number) const { return !op_gt(number); }
                     inline bool ArbInt::op_ne (ArbInt     const& number) const { return !op_eq(number); }
  template <class T> inline bool ArbInt::op_ne (SafeInt<T>        number) const { return !op_eq(number); }
  template <class T> inline bool ArbInt::op_ne (T                 number) const { return !op_eq(number); }
  
  // Bitwise AND with an integral type.
  template <class T> ArbInt& ArbInt::op_bit_and (SafeInt<T> number) {
    
    // FIXME: Negatives should be allowed here.
    // No negatives.
    if (number < 0) {
      throw ArbIntErrors::Negative();
    }
    
    // If the number is too large to AND directly, resort to conversion to
    // ArbInt then AND.
    if (number >= s_digitbase) {
      
      // Poopyfarts!
      return op_bit_and(ArbInt(number));
      
    // Otherwise AND directly.
    } else {
      
      // If this number is 0, nothing needs to be done.
      if (isZero()) {
        return *this;
      }
      
      // Work area, but don't bother copying anything more than the least
      // significant digit. In fact, do the AND right here, it's easy.
      ArbInt retval((*(_digits))[0] & number);
      
      // Copy into place and return.
      _digits = retval._digits;
      return *this;
      
    }
    
  }
  template <class T> inline ArbInt& ArbInt::op_bit_and (T number) { return op_bit_and(SafeInt<T>(number)); }
  
  // Bitwise inclusive OR with an integral type.
  template <class T> ArbInt& ArbInt::op_bit_ior (SafeInt<T> number) {
    
    // FIXME: Negatives should be allowed here.
    // No negatives.
    if (number < 0) {
      throw ArbIntErrors::Negative();
    }
    
    // If the number is too large to OR directly, resort to conversion to
    // ArbInt then OR.
    if (number >= s_digitbase) {
      
      // Stinknugget.
      return op_bit_ior(ArbInt(number));
      
    // Otherwise OR directly.
    } else {
      
      // If this number is 0, simply set with number.
      if (isZero()) {
        return set(number);
      }
      
      // Copy digits and OR.
      ArbInt retval(*this, true);
      (*(retval._digits))[0] = (*(retval._digits))[0] | number;
      
      // Move the result into place and return.
      _digits = retval._digits;
      return *this;
      
    }
    
  }
  template <class T> inline ArbInt& ArbInt::op_bit_ior (T number) { return op_bit_ior(SafeInt<T>(number)); }
  
  // Bitwise exclusive OR with an integral type.
  template <class T> ArbInt& ArbInt::op_bit_xor (SafeInt<T> number) {
    
    // FIXME: Negatives should be allowed here.
    // No negatives.
    if (number < 0) {
      throw ArbIntErrors::Negative();
    }
    
    // If the number is too large to OR directly, resort to conversion to
    // ArbInt then OR.
    if (number >= s_digitbase) {
      
      // Blargh.
      return op_bit_xor(ArbInt(number));
      
    // Otherwise OR directly.
    } else {
      
      // If this number is 0, simply set with number.
      if (isZero()) {
        return set(number);
      }
      
      // Copy digits and OR.
      ArbInt retval(*this, true);
      (*(retval._digits))[0] = (*(retval._digits))[0] ^ number;
      
      // Move the result into place and return.
      _digits = retval._digits;
      return *this;
      
    }
    
  }
  template <class T> inline ArbInt& ArbInt::op_bit_xor (T number) { return op_bit_xor(SafeInt<T>(number)); }
  
  // Tests if this number is equal to zero.
  inline bool ArbInt::isZero () const { return _digits->empty(); }
  
  // Tests if this number is odd or even.
  inline bool ArbInt::isOdd  () const { return !isZero() && (_digits->front() & 1); }
  inline bool ArbInt::isEven () const { return !isOdd();                            }
  
  // Placeholder for automatic pow conversion.
  template <class T> inline ArbInt ArbInt::pow (T const exp) { return pow(ArbInt(exp)); }
  
  // Return the maximum string input base.
  inline ArbInt::value_type ArbInt::max_input_base () { return SafeInt<value_type>(s_numidigits); }
  
  // Trim insignificant zeros.
  inline ArbInt& ArbInt::_trimZeros () { s_trimZerosE(*_digits); return *this; }
  
  // Trim leading and trailing zeros from a given container.
  template <class T> inline void ArbInt::s_trimZeros (T& c) { s_trimZerosB(c); s_trimZerosE(c); }
  
  // Trim leading zeros from a given container.
  template <class T> void ArbInt::s_trimZerosB (T& c) {
    
    // Nothing to do if empty.
    if (!c.empty()) {
      
      // Work data.
      typename T::iterator pos;
      
      // Trim leading zeros.
      for (pos = c.begin(); (pos != c.end()) && (*pos == 0); ++pos) {}
      if (pos >= c.begin()) {
        c.erase(c.begin(), pos);
      }
      
    }
    
  }
  
  // Trim trailing zeros from a given container.
  template <class T> void ArbInt::s_trimZerosE (T& c) {
    
    // Nothing to do if empty.
    if (!c.empty()) {
      
      // Work data.
      typename T::iterator pos;
      
      // Trim trailing zeros.
      for (pos = (c.end() - 1); (pos != (c.begin() - 1)) && (*pos == 0); --pos) {}
      if (pos++ < (c.end() - 1)) {
        c.erase(pos, c.end());
      }
      
    }
    
  }
  
  // Do long division on a given container in the specified base. Divisor
  // type must be 2x base. This is not checked, so be careful!
  template <class DivndT, class DivorT> DivorT ArbInt::s_longDiv (DivndT& divnd, DivorT divor, value_type base) {
    
    // Group of digits to divide.
    SafeInt<DivorT> dgroup;
    SafeInt<DivorT> dquot;
    
    // Quotient.
    DivndT quotient;
    
    // Long division steps through each digit of the dividend.
    for (typename DivndT::reverse_iterator i = divnd.rbegin(); i != divnd.rend(); ++i) {
      
      // Add this digit to the group.
      dgroup += *i;
      
      // Divide the group and add the result to the quotient.
      dquot = dgroup / divor;
      quotient.insert(quotient.begin(), dquot);
      
      // Take out what we've divided.
      dgroup -= dquot * divor;
      
      // Move the remainder up to the next order of magnitude.
      dgroup *= base;
      
    }
    
    // Trim insignificant zeros from the quotient.
    s_trimZerosE(quotient);
    
    // Set the result in place.
    divnd.swap(quotient);
    
    // Undo the last base shift, this is the remainder. Return it.
    return dgroup / base;
    
  }
  
  // Convert a container from one base to another. Frombase must be
  // 2^(bits/2) of from or smaller, tobase must be 2^(bits/2) of to or
  // smaller.
  template <class FT, class TT> void ArbInt::s_baseConv (FT const& from, value_type frombase, TT& to, value_type tobase) {
    
    // Verify that bases are valid. Base must be at least two, and at most
    // half of the significant bits of the target container's number type.
    // Maximum base is static, and so should only be calculated once per
    // type combination.
    static SafeInt<typename TT::value_type> maxbase = rppower(SafeInt<typename TT::value_type>(2), std::numeric_limits<typename TT::value_type>::digits >> 1);
    if (SafeInt<value_type>(frombase) < 2) {
      throw ArbIntErrors::BaseOutOfRangeMin<value_type, value_type>().Base(frombase).Limit(2);
    }
    if (SafeInt<value_type>(tobase) < 2) {
      throw ArbIntErrors::BaseOutOfRangeMin<value_type, value_type>().Base(tobase).Limit(2);
    }
    if (SafeInt<value_type>(frombase) > maxbase) {
      throw ArbIntErrors::BaseOutOfRangeMax<value_type, value_type>().Base(frombase).Limit(maxbase);
    }
    if (SafeInt<value_type>(tobase) > maxbase) {
      throw ArbIntErrors::BaseOutOfRangeMax<value_type, value_type>().Base(tobase).Limit(maxbase);
    }
    
    // Empty out target container.
    to.clear();
    
    // Temporary, since work will be done in place.
    FT tmp_from(from);
    
    // Convert base by storing the remainder of repeated division by the
    // base that we will be converting to, in the base that we are
    // converting from. Least significant digits come out first.
    while (tmp_from.size() > 0) {
      to.push_back(s_longDiv(tmp_from, tobase, frombase));
    }
    
  }
  
  // Determine number type.
  template <class T> ArbInt::_NumType const ArbInt::_GetNumType<T>::value =
    std::numeric_limits<T>::is_integer ? (
      std::numeric_limits<T>::is_signed ? (
        _NUM_SINT
      ) : (
        _NUM_UINT
      )
    ) : (
      _NUM_FLPT
    )
  ;
  
  // Set from an unsigned integer type.
  template <class T> void ArbInt::_Set<T, ArbInt::_NUM_UINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // Work area.
    ArbInt::_DataPT new_digits(new ArbInt::_DigsT);
    
    // Only something to set if the number is not zero.
    if (r != 0) {
      
      // If the number is less than base, simply set it.
      if (r < s_digitbase) {
        
        // Easy :)
        new_digits->push_back(r);
        
      // Otherwise do full conversion.
      } else {
        
        // Convert with repeated division.
        SafeInt<T> tmp = r;
        while (tmp) {
          new_digits->push_back(tmp % s_digitbase);
          tmp /= s_digitbase;
        }
        
      }
    }
    
    // Swap in the new digits and return.
    l._digits = new_digits;
    
  }
  template <class T> inline void ArbInt::_Set<T, ArbInt::_NUM_UINT>::op (ArbInt& l, T const r) { ArbInt::_Set<T, ArbInt::_NUM_UINT>::op(l, SafeInt<T>(r)); }
  
  // Set from a signed integer type.
  template <class T> void ArbInt::_Set<T, ArbInt::_NUM_SINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // If we were sent a negative number, error.
    if (r < 0) {
      throw ArbIntErrors::NegativeSet<T>().Source(r);
    }
    
    // Set.
    ArbInt::_Set<T, ArbInt::_NUM_UINT>::op(l, r);
    
  }
  template <class T> inline void ArbInt::_Set<T, ArbInt::_NUM_SINT>::op (ArbInt& l, T const r) { ArbInt::_Set<T, ArbInt::_NUM_SINT>::op(l, SafeInt<T>(r)); }
  
  // Set from a floating-point type.
  template <class T> void ArbInt::_Set<T, ArbInt::_NUM_FLPT>::op (ArbInt& l, T const r) {
    
    // Round to the nearest whole number.
    T tmp = floor(r + 0.5);
    
    // If we were sent a negative number, error.
    if (tmp < 0) {
      throw ArbIntErrors::NegativeSet<T>().Source(r);
    }
    
    // Convert to string and set.
    l.set(DAC::toString(r));
    
  }
  
  // Multiply by an unsigned integer type.
  template <class T> void ArbInt::_Mul<T, ArbInt::_NUM_UINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // If the number is too large to do in one step, resort to conversion to
    // ArbInt then multiply.
    if (r >= s_digitbase) {
      l.op_mul(ArbInt(r));
      return;
    }
    
    // If we were sent zero, blank the digits.
    if (r == 0) {
      l._digits = new ArbInt::_DigsT;
      return;
    }
    
    // If we were sent 1, easy.
    if (r == 1) {
      return;
    }
    
    // Work area;
    ArbInt retval;
    
    // Multiply like 3rd grade.
    for (ArbInt::_DigsT::size_type i = 0; i != l._digits->size(); ++i) {
      
      // Create a new digit if necessary.
      if (retval._digits->size() == i) {
        retval._digits->push_back(0);
      }
      
      // Multiply the digit and carry.
      (*(retval._digits))[i] += (*(l._digits))[i] * r;
      retval._carry(i);
      
    }
    
    // Move the digits into place and return.
    l._digits = retval._digits;
    
  }
  template <class T> inline void ArbInt::_Mul<T, ArbInt::_NUM_UINT>::op (ArbInt& l, T const r) { ArbInt::_Mul<T, ArbInt::_NUM_UINT>::op(l, SafeInt<T>(r)); }
  
  // Multiply by a signed integer type.
  template <class T> void ArbInt::_Mul<T, ArbInt::_NUM_SINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // If we were sent a negative number, error.
    if (r < 0) {
      throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("*").Right(r);
    }
    
    // OK, now multiply.
    ArbInt::_Mul<T, ArbInt::_NUM_UINT>::op(l, r);
    
  }
  template <class T> inline void ArbInt::_Mul<T, ArbInt::_NUM_SINT>::op (ArbInt& l, T const r) { ArbInt::_Mul<T, ArbInt::_NUM_SINT>::op(l, SafeInt<T>(r)); }
  
  // Multiply by a floating-point type.
  template <class T> void ArbInt::_Mul<T, ArbInt::_NUM_FLPT>::op (ArbInt& l, T const r) {
    
    // Round to the nearest whole number.
    T tmp = floor(r + 0.5);
    
    // If we were sent a negative number, error.
    if (tmp < 0) {
      throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("*").Right(r);
    }
    
    // Now convert to ArbInt and multiply.
    l.op_mul(ArbInt(tmp));
    
  }
  
  // Divide by an unsigned integer type.
  template <class T> void ArbInt::_Div<T, ArbInt::_NUM_UINT>::op (ArbInt& l, SafeInt<T> const r, ArbInt* const remainder) {
    
    // Cannot divide by zero.
    if (r == 0) {
      throw ArbIntErrors::DivByZeroBinary<ArbInt, T>().Left(l).Operator("/").Right(r);
    }
    
    // If the number is too large to do in one step, resort to conversion to
    // ArbInt then divide.
    if (r >= ArbInt::s_digitbase) {
      l.op_div(ArbInt(r), remainder);
      return;
    }
    
    // If dividing by 1, easy, remainder is zero and return.
    if (r == 1) {
      if (remainder) {
        *remainder = 0;
      }
      return;
    }
    
    // Work area.
    ArbInt retval(l, *true);
    
    // Already wrote the long division algorithm, reuse it. Different calls
    // for remainder or not.
    if (remainder) {
      *remainder = s_longDiv((*(retval._digits)), static_cast<T>(number), s_digitbase);
    } else {
      s_longDiv((*(retval._digits)), static_cast<T>(number), s_digitbase);
    }
    
    // Move the digits into place and return.
    l._digits = retval._digits;
    
  }
  template <class T> inline void ArbInt::_Div<T, ArbInt::_NUM_UINT>::op (ArbInt& l, T const r, ArbInt* const remainder) { ArbInt::_Div<T, ArbInt::_NUM_UINT>::op(l, SafeInt<T>(r), remainder); }
  
  // Divide by a signed integer type.
  template <class T> void ArbInt::_Div<T, ArbInt::_NUM_SINT>::op (ArbInt& l, SafeInt<T> const r, ArbInt* const remainder) {
    
    // Cannot return a negative number.
    if (r < 0) {
      throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("/").Right(r);
    }
    
    // OK, now divide.
    ArbInt::_Div<T, ArbInt::_NUM_UINT>::op(l, r, remainder);
    
  }
  template <class T> inline void ArbInt::_Div<T, ArbInt::_NUM_SINT>::op (ArbInt& l, T const r, ArbInt* const remainder) { ArbInt::_Div<T, ArbInt::_NUM_SINT>::op(l, SafeInt<T>(r), remainder); }
  
  // Divide by a floating-point type.
  template <class T> void ArbInt::_Div<T, ArbInt::_NUM_FLPT>::op (ArbInt& l, T const r, ArbInt* const remainder) {
    
    // Round to the nearest whole number.
    T tmp = floor(r + 0.5);
    
    // Cannot divide by zero.
    if (tmp == 0) {
      throw ArbIntErrors::DivByZeroBinary<ArbInt, T>().Left(l).Operator("/").Right(r);
    }
    
    // If we were sent a negative number, error.
    if (tmp < 0) {
      throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("/").Right(r);
    }
    
    // Now convert to ArbInt and divide.
    l.op_div(Arbint(tmp));
    
  }
  
  // Modulo divide by an unsigned integer type.
  template <class T> void ArbInt::_Mod<T, ArbInt::_NUM_UINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // Work area.
    ArbInt retval;
    ArbInt quotient(l);
    
    // Do division, translate any errors.
    try {
      quotient.op_div(r, &retval);
    } catch (ArbIntErrors::DivByZeroBinary<ArbInt, T>) {
      throw ArbIntErrors::DivByZeroBinary<ArbInt, T>().Left(l).Operator("%").Right(r);
    } catch (ArbIntErrors::DivByZeroBinary<ArbInt, ArbInt>) {
      throw ArbIntErrors::DivByZeroBinary<ArbInt, T>().Left(l).Operator("%").Right(r);
    }
    
    // Copy remainder into place and return.
    l._digits = retval._digits;
    
  }
  template <class T> inline void ArbInt::_Mod<T, ArbInt::_NUM_UINT>::op (ArbInt& l, T const r) { ArbInt::_Mod<T, ArbInt::_NUM_UINT>(l, SafeInt<T>(r)); }
  
  // Modulo divide by a signed integer type.
  template <class T> void ArbInt::_Mod<T, ArbInt::_NUM_SINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // Modulo division by a negative number does not affect the sign of the
    // result, so use the absolute value. Catch the rare circumstance where
    // the data type's minimum value is sent and convert to ArbInt before
    // dividing. Negate before converting with the ~x + 1 trick. This is a
    // hack, but there is no better way to get around type limit without
    // making this function aware of type sizes.
    if (r < 0) {
      try {
        ArbInt::_Mod<T, ArbInt::_NUM_UINT>(l, -r);
      } catch (SafeIntErrors::UnOpOverflow<T>) {
        l.op_mod(ArbInt(~r) + 1);
      }
    } else {
      ArbInt::_Mod<T, ArbInt::_NUM_UINT>(l, r);
    }
    
  }
  template <class T> inline void ArbInt::_Mod<T, ArbInt::_NUM_SINT>::op (ArbInt& l, T const r) { ArbInt::_Mod<T, ArbInt::_NUM_SINT>(l, SafeInt<T>(r)); }
  
  // Modulo divide by a floating-point type.
  template <class T> void ArbInt::_Mod<T, ArbInt::_NUM_FLPT>::op (ArbInt& l, T const r) {
    
    // Round to the nearest whole number.
    T tmp = floor(r + 0.5);
    
    // Sign does not matter, so get abs.
    if (tmp < 0) {
      tmp = -tmp;
    }
    
    // Now convert to ArbInt and divide. Convert any errors.
    try {
      l.op_mod(ArbInt(tmp));
    } catch (ArbIntErrors::DivByZeroBinary<ArbInt, ArbInt>) {
      throw ArbIntErrors::DivByZeroBinary<ArbInt, T>().Left(l).Operator("%").Right(r);
    }
    
  }
  
  // Add an unsigned integer type.
  template <class T> void ArbInt::_Add<T, ArbInt::_NUM_UINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // If the number is too large to add directly, resort to conversion to
    // ArbInt then add.
    if (l >= ArbInt::s_digitbase) {
      l.op_add(ArbInt(r));
      return;
    }
    
    // Nothing to do if adding 0.
    if (r == 0) {
      return *this;
    }
    
    // Work area.
    ArbInt retval(l, true);
    
    // Add and carry or create a digit if necessary.
    if (retval._digits->empty()) {
      retval._digits->push_back(number);
    } else {
      (*(retval._digits))[0] += number;
      retval._carry(0);
    }
    
    // Move the digits into place and return.
    l._digits = retval._digits;
    
  }
  template <class T> inline void ArbInt::_Add<T, ArbInt::_NUM_UINT>::op (ArbInt& l, T const r) { ArbInt::_Add<T, ArbInt::_NUM_UINT>(l, SafeInt<T>(r)); }
  
  // Add a signed integer type.
  template <class T> void ArbInt::_Add<T, ArbInt::_NUM_SINT>::op (ArbInt& l, SafeInt<T> const r) {
        
    // If adding a negative, subtract the opposite. Use the same trick as in
    // _Mod to convert to a positive number.
    if (r < 0) {
      
      // Catch any negative errors and convert the operator.
      try {
        try {
          ArbInt::_Sub<T, ArbInt::_NUM_UINT>(l, -r);
        } catch (SafeIntErrors::UnOpOverflow<T>) {
          l.op_sub(ArbInt(~r) + 1);
        }
      } catch (ArbIntErrors::NegativeBinary<ArbInt, T>) {
        throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("+").Right(r);
      } catch (ArbIntErrors::NegativeBinary<ArbInt, ArbInt>) {
        throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("+").Right(r);
      }
      
    // Otherwise add normally.
    } else {
      ArbInt::_Add<T, ArbInt::_NUM_UINT>(l, r);
    }
    
  }
  template <class T> inline void ArbInt::_Add<T, ArbInt::_NUM_SINT>::op (ArbInt& l, T const r) { ArbInt::_Add<T, ArbInt::_NUM_SINT>(l, SafeInt<T>(r)); }
  
  // Add a floating-point type.
  template <class T> void ArbInt::_Add<T, ArbInt::_NUM_FLPT>::op (ArbInt& l, T const r) {
    
    // Round to the nearest whole number.
    T tmp = floor(r + 0.5);
    
    // If adding a negative, subtract the opposite.
    if (tmp < 0) {
      
      // Catch any negative errors and convert the operator.
      try {
        l.op_sub(ArbInt(r * -1.0));
      } catch (ArbIntErrors::NegativeBinary<ArbInt, Arbint>) {
        throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("+").Right(r);
      }
      
    // Otherwise add normally.
    } else {
      l.op_add(ArbInt(r));
    }
    
  }
  
  // Subtract an unsigned integer type.
  template <class T> void ArbInt::_Sub<T, ArbInt::_NUM_UINT>::op (ArbInt& l, SafeInt<T> const r) {
    
    // If the number is too large to subtract directly, resort to conversion
    // to ArbInt then subtract. Convert any errors thrown.
    if (l >= ArbInt::s_digitbase) {
      try {
        l.op_sub(ArbInt(r));
      } catch (ArbIntErrors::NegativeBinary<ArbInt, ArbInt>) {
        throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("+").Right(r);
      }
      return;
    }
    
    // Nothing to do if subtracting 0.
    if (l == 0) {
      return;
    }
    
    // If subtraction will result in a negative, error.
    if (r > l) {
      throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("-").Right(number);
    }
    
    // Work area.
    ArbInt retval(l, true);
    
    // Borrow if necessary and subtract.
    if ((*(retval._digits))[0] < l) {
      retval._borrow(0);
    }
    (*(retval._digits))[0] -= number;
    
    // Trim zeros.
    retval._trimZeros();
    
    // Move the digits into place and return.
    l._digits = retval._digits;
    
  }
  template <class T> inline void ArbInt::_Sub<T, ArbInt::_NUM_UINT>::op (ArbInt& l, T const r) { ArbInt::_Sub<T, ArbInt::_NUM_UINT>(l, SafeInt<T>(r)); }
  
  // Subtract a signed integer type.
  template <class T> void ArbInt::_Sub<T, ArbInt::_NUM_SINT>::op (ArbInt& l, SafeInt<T> const r) {
        
    // If subtracting a negative, add the opposite.
    if (r < 0) {
      
      //  Use the same trick as in _Mod to convert to a positive number.
      try {
        ArbInt::_Add<T, ArbInt::_NUM_UINT>(l, -r);
      } catch (SafeIntErrors::UnOpOverflow<T>) {
        l.op_add(ArbInt(~r) + 1);
      }
      
    // Otherwise subtract normally.
    } else {
      ArbInt::_Sub<T, ArbInt::_NUM_UINT>(l, r);
    }
    
  }
  template <class T> inline void ArbInt::_Sub<T, ArbInt::_NUM_SINT>::op (ArbInt& l, T const r) { ArbInt::_Sub<T, ArbInt::_NUM_SINT>(l, SafeInt<T>(r)); }
  
  // Subtract a floating-point type.
  template <class T> void ArbInt::_Sub<T, ArbInt::_NUM_FLPT>::op (ArbInt& l, T const r) {
    
    // Round to the nearest whole number.
    T tmp = floor(r + 0.5);
    
    // If subtracting a negative, add the opposite, otherwise subtract
    // normally.
    if (tmp < 0) {
      l.op_add(ArbInt(r * -1.0));
    } else {
      
      // Catch and convert any errors thrown.
      try {
        l.op_sub(ArbInt(r));
      } catch (ArbIntErrors::NegativeBinary<ArbInt, ArbInt>) {
        throw ArbIntErrors::NegativeBinary<ArbInt, T>().Left(l).Operator("+").Right(r);
      }
      
    }
    
  }
  
  /*
      // Shift left.
      template <class T, _NumType> class _ShL;
      template <class T> class _ShL<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShL<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShL<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Shift right.
      template <class T, _NumType> class _ShR;
      template <class T> class _ShR<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShR<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _ShR<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Greater than.
      template <class T, _NumType> class _GT;
      template <class T> class _GT<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _GT<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _GT<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Greater than or equal to.
      template <class T, _NumType> class _GE;
      template <class T> class _GE<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _GE<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _GE<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Less than.
      template <class T, _NumType> class _LT;
      template <class T> class _LT<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _LT<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _LT<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Less than or equal to.
      template <class T, _NumType> class _LE;
      template <class T> class _LE<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _LE<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _LE<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Equal to.
      template <class T, _NumType> class _EQ;
      template <class T> class _EQ<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _EQ<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _EQ<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Not equal to.
      template <class T, _NumType> class _NE;
      template <class T> class _NE<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _NE<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _NE<T, _NUM_FLPT> { public:                                                  static void op (ArbInt& l, T const r); };
      
      // Bitwise AND.
      template <class T, _NumType> class _Bit_AND;
      template <class T> class _Bit_AND<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _Bit_AND<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      
      // Bitwise inclusive OR.
      template <class T, _NumType> class _Bit_IOR;
      template <class T> class _Bit_IOR<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _Bit_IOR<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      
      // Bitwise exclusive OR.
      template <class T, _NumType> class _Bit_XOR;
      template <class T> class _Bit_XOR<T, _NUM_UINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
      template <class T> class _Bit_XOR<T, _NUM_SINT> { public: static void op (ArbInt& l, SafeInt<T> const& r); static void op (ArbInt& l, T const r); };
   */
      
  /***************************************************************************
   * Errors.
   ***************************************************************************/
  namespace ArbIntErrors {
    
    inline BadFormat& BadFormat::Problem  (char const*                        const  problem)  throw() { _problem  = problem;  return *this; }
    inline BadFormat& BadFormat::Position (std::string::size_type             const  position) throw() { _position = position; return *this; }
    inline BadFormat& BadFormat::Number   (ConstReferencePointer<std::string> const& number)   throw() { _number   = number;   return *this; }
    inline char const*                        BadFormat::Problem  () const throw() { return _problem;  }
    inline std::string::size_type             BadFormat::Position () const throw() { return _position; }
    inline ConstReferencePointer<std::string> BadFormat::Number   () const throw() { return _number;   }
    
    template <class T> char const* NegativeSet<T>::what () const throw() {
      try {
        return (DAC::toString(_source) + ": Attempt to set ArbInt to a negative number.").c_str();
      } catch (...) {
        return "Attempt to set ArbInt to a negative number. Error creating message string.";
      }
    }
    template <class T> inline NegativeSet<T>& NegativeSet<T>::Source (T const source) throw() { _source = source; return *this; }
    template <class T> inline T NegativeSet<T>::Source () const throw() { return _source; }
    
    inline NegativeUnary& NegativeUnary::Number   (ArbInt      const& number) throw() { _number = number; return *this; }
    inline NegativeUnary& NegativeUnary::Operator (char const* const  op)     throw() { _op     = op;     return *this; }
    inline NegativeUnary& NegativeUnary::Prefix   (bool        const  prefix) throw() { _prefix = prefix; return *this; }
    inline ArbInt      NegativeUnary::Number   () const throw() { return _number; }
    inline char const* NegativeUnary::Operator () const throw() { return _op;     }
    inline bool        NegativeUnary::Prefix   () const throw() { return _prefix; }
    
    template <class T, class U> char const* NegativeBinary<T, U>::what () const throw() {
      try {
        return (DAC::toString(_l) + " " + std::string(_op) + " " + DAC::toString(_r) + ": Results in a negative number.").c_str();
      } catch (...) {
        return "Binary operation results in a negative number. Error creating message string.";
      }
    }
    template <class T, class U> inline NegativeBinary<T, U>& NegativeBinary<T, U>::Left     (T           const l)  throw() { _l  = l;  return *this; }
    template <class T, class U> inline NegativeBinary<T, U>& NegativeBinary<T, U>::Operator (char const* const op) throw() { _op = op; return *this; }
    template <class T, class U> inline NegativeBinary<T, U>& NegativeBinary<T, U>::Right    (U           const r)  throw() { _r  = r;  return *this; }
    template <class T, class U> inline T           NegativeBinary<T, U>::Left     () const throw() { return _l;  }
    template <class T, class U> inline char const* NegativeBinary<T, U>::Operator () const throw() { return _op; }
    template <class T, class U> inline U           NegativeBinary<T, U>::Right    () const throw() { return _r;  }
    
    template <class T> char const* OverrunSpecialized<T>::what () const throw() {
      try {
        return (std::string(_problem) + " at offset " + DAC::toString(_offset) + " with limit of " + DAC::toString(_limit) + ".").c_str();
      } catch (...) {
        return "Instruction overruns end of container. Error creating message string.";
      }
    }
    template <class T> inline OverrunSpecialized<T>& OverrunSpecialized<T>::Problem (char const* const problem) throw() { _problem = problem; return *this; }
    template <class T> inline OverrunSpecialized<T>& OverrunSpecialized<T>::Offset  (T           const offset)  throw() { _offset  = offset;  return *this; }
    template <class T> inline OverrunSpecialized<T>& OverrunSpecialized<T>::Limit   (T           const limit)   throw() { _limit   = limit;   return *this; }
    template <class T> inline char const* OverrunSpecialized<T>::Problem () const throw() { return _problem; }
    template <class T> inline T           OverrunSpecialized<T>::Offset  () const throw() { return _offset;  }
    template <class T> inline T           OverrunSpecialized<T>::Limit   () const throw() { return _limit;   }
    
    template <class T, class U> char const* DivByZeroBinary<T, U>::what () const throw() {
      try {
        return (DAC::toString(_l) + " " + std::string(_op) + " " + DAC::toString(_r) + ": Divide by zero.").c_str();
      } catch (...) {
        return "Divide by zero. Error creating message string.";
      }
    }
    template <class T, class U> inline DivByZeroBinary<T, U>& DivByZeroBinary<T, U>::Left     (T           const l)  throw() { _l  = l;  return *this; }
    template <class T, class U> inline DivByZeroBinary<T, U>& DivByZeroBinary<T, U>::Operator (char const* const op) throw() { _op = op; return *this; }
    template <class T, class U> inline DivByZeroBinary<T, U>& DivByZeroBinary<T, U>::Right    (U           const r)  throw() { _r  = r;  return *this; }
    template <class T, class U> inline T           DivByZeroBinary<T, U>::Left     () const throw() { return _l;  }
    template <class T, class U> inline char const* DivByZeroBinary<T, U>::Operator () const throw() { return _op; }
    template <class T, class U> inline U           DivByZeroBinary<T, U>::Right    () const throw() { return _r;  }
    
    template <class T> char const* ScalarOverflowSpecialized<T>::what () const throw() {
      try {
        return (_number.toString() + ": Oveflows requested scalar type's limit of " + DAC::toString(_limit) + ".").c_str();
      } catch (...) {
        return "ArbInt overflows requested scalar type. Error creating message string.";
      }
    }
    template <class T> inline ScalarOverflowSpecialized<T>& ScalarOverflowSpecialized<T>::Number (ArbInt const& number) throw() { _number = number; return *this; }
    template <class T> inline ScalarOverflowSpecialized<T>& ScalarOverflowSpecialized<T>::Limit  (T      const  limit)  throw() { _limit  = limit;  return *this; }
    template <class T> inline ArbInt ScalarOverflowSpecialized<T>::Number () const throw() { return _number; }
    template <class T> inline T      ScalarOverflowSpecialized<T>::Limit  () const throw() { return _limit;  }
    
    template <class T, class U> char const* BaseOutOfRangeSpecialized<T, U>::what () const throw() {
      try {
        return (DAC::toString(_base) + ": Requested base is out of range, limit is " + DAC::toString(_limit) + ".").c_str();
      } catch (...) {
        return "Requested base is out of range. Error creating message string.";
      }
    }
    template <class T, class U> inline BaseOutOfRangeSpecialized<T, U>& BaseOutOfRangeSpecialized<T, U>::Base  (T const base)  throw() { _base  = base;  return *this; }
    template <class T, class U> inline BaseOutOfRangeSpecialized<T, U>& BaseOutOfRangeSpecialized<T, U>::Limit (U const limit) throw() { _limit = limit; return *this; }
    template <class T, class U> inline T BaseOutOfRangeSpecialized<T, U>::Base  () const throw() { return _base;  }
    template <class T, class U> inline U BaseOutOfRangeSpecialized<T, U>::Limit () const throw() { return _limit; }
    
    template <class T, class U> char const* BaseOutOfRangeMin<T, U>::what () const throw() {
      try {
        return (DAC::toString(this->Base()) + ": Requsted range is below minimum base of " + DAC::toString(this->Limit()) + ".").c_str();
      } catch (...) {
        return "Requested base is below minimum. Error creating message string.";
      }
    }
    
    template <class T, class U> char const* BaseOutOfRangeMax<T, U>::what () const throw() {
      try {
        return (DAC::toString(this->Base()) + ": Requsted range is above maximum base of " + DAC::toString(this->Limit()) + ".").c_str();
      } catch (...) {
        return "Requested base is above maximum. Error creating message string.";
      }
    }
    
    inline RootTooLarge& RootTooLarge::Number (ArbInt const& number) throw() { _number = number; return *this; }
    inline RootTooLarge& RootTooLarge::Root   (ArbInt const& root)   throw() { _root   = root;   return *this; }
    inline ArbInt RootTooLarge::Number () const throw() { return _number; }
    inline ArbInt RootTooLarge::Root   () const throw() { return _root;   }
    
  }
  
  /***************************************************************************
   * Operators.
   ***************************************************************************/
  
  // Stream I/O operators.
  inline std::ostream&       operator << (std::ostream&       l, ArbInt const& r) { l << r.toString();                                  return l; }
  inline std::ostringstream& operator << (std::ostringstream& l, ArbInt const& r) { l << r.toString();                                  return l; }
  inline std::istream&       operator >> (std::istream&       l, ArbInt&       r) { std::string input; std::cin >> input; r.set(input); return l; }
  
  // Arithmetic operators.
                     inline ArbInt operator * (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_mul(r); }
  template <class T> inline ArbInt operator * (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_mul(r); }
  template <class T> inline ArbInt operator * (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(r).op_mul(l); }
  template <class T> inline ArbInt operator * (ArbInt     const& l, T          const  r) { return ArbInt(l).op_mul(r); }
  template <class T> inline ArbInt operator * (T          const  l, ArbInt     const& r) { return ArbInt(r).op_mul(l); }
                     inline ArbInt operator / (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_div(r); }
  template <class T> inline ArbInt operator / (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_div(r); }
  template <class T> inline ArbInt operator / (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(l).op_div(r); }
  template <class T> inline ArbInt operator / (ArbInt     const& l, T          const  r) { return ArbInt(l).op_div(r); }
  template <class T> inline ArbInt operator / (T          const  l, ArbInt     const& r) { return ArbInt(l).op_div(r); }
                     inline ArbInt operator % (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_mod(r); }
  template <class T> inline ArbInt operator % (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_mod(r); }
  template <class T> inline ArbInt operator % (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(l).op_mod(r); }
  template <class T> inline ArbInt operator % (ArbInt     const& l, T          const  r) { return ArbInt(l).op_mod(r); }
  template <class T> inline ArbInt operator % (T          const  l, ArbInt     const& r) { return ArbInt(l).op_mod(r); }
                     inline ArbInt operator + (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_add(r); }
  template <class T> inline ArbInt operator + (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_add(r); }
  template <class T> inline ArbInt operator + (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(r).op_add(l); }
  template <class T> inline ArbInt operator + (ArbInt     const& l, T          const  r) { return ArbInt(l).op_add(r); }
  template <class T> inline ArbInt operator + (T          const  l, ArbInt     const& r) { return ArbInt(r).op_add(l); }
                     inline ArbInt operator - (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_sub(r); }
  template <class T> inline ArbInt operator - (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_sub(r); }
  template <class T> inline ArbInt operator - (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(l).op_sub(r); }
  template <class T> inline ArbInt operator - (ArbInt     const& l, T          const  r) { return ArbInt(l).op_sub(r); }
  template <class T> inline ArbInt operator - (T          const  l, ArbInt     const& r) { return ArbInt(l).op_sub(r); }
  
  // Bit shift operators.
                     inline ArbInt operator << (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_shl(r); }
  template <class T> inline ArbInt operator << (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_shl(r); }
  template <class T> inline ArbInt operator << (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(l).op_shl(r); }
  template <class T> inline ArbInt operator << (ArbInt     const& l, T          const  r) { return ArbInt(l).op_shl(r); }
  template <class T> inline ArbInt operator << (T          const  l, ArbInt     const& r) { return ArbInt(l).op_shl(r); }
                     inline ArbInt operator >> (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_shr(r); }
  template <class T> inline ArbInt operator >> (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_shr(r); }
  template <class T> inline ArbInt operator >> (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(l).op_shr(r); }
  template <class T> inline ArbInt operator >> (ArbInt     const& l, T          const  r) { return ArbInt(l).op_shr(r); }
  template <class T> inline ArbInt operator >> (T          const  l, ArbInt     const& r) { return ArbInt(l).op_shr(r); }
  
  // Comparsion operators.
                     inline bool operator >  (ArbInt     const& l, ArbInt     const& r) { return  l.op_gt(r); }
  template <class T> inline bool operator >  (ArbInt     const& l, SafeInt<T> const  r) { return  l.op_gt(r); }
  template <class T> inline bool operator >  (SafeInt<T> const  l, ArbInt     const& r) { return !r.op_ge(l); }
  template <class T> inline bool operator >  (ArbInt     const& l, T          const  r) { return  l.op_gt(r); }
  template <class T> inline bool operator >  (T          const  l, ArbInt     const& r) { return !r.op_ge(l); }
                     inline bool operator >= (ArbInt     const& l, ArbInt     const& r) { return  l.op_ge(r); }
  template <class T> inline bool operator >= (ArbInt     const& l, SafeInt<T> const  r) { return  l.op_ge(r); }
  template <class T> inline bool operator >= (SafeInt<T> const  l, ArbInt     const& r) { return !r.op_gt(l); }
  template <class T> inline bool operator >= (ArbInt     const& l, T          const  r) { return  l.op_ge(r); }
  template <class T> inline bool operator >= (T          const  l, ArbInt     const& r) { return !r.op_gt(l); }
                     inline bool operator <  (ArbInt     const& l, ArbInt     const& r) { return  l.op_lt(r); }
  template <class T> inline bool operator <  (ArbInt     const& l, SafeInt<T> const  r) { return  l.op_lt(r); }
  template <class T> inline bool operator <  (SafeInt<T> const  l, ArbInt     const& r) { return !r.op_le(l); }
  template <class T> inline bool operator <  (ArbInt     const& l, T          const  r) { return  l.op_lt(r); }
  template <class T> inline bool operator <  (T          const  l, ArbInt     const& r) { return !r.op_le(l); }
                     inline bool operator <= (ArbInt     const& l, ArbInt     const& r) { return  l.op_le(r); }
  template <class T> inline bool operator <= (ArbInt     const& l, SafeInt<T> const  r) { return  l.op_le(r); }
  template <class T> inline bool operator <= (SafeInt<T> const  l, ArbInt     const& r) { return !r.op_lt(l); }
  template <class T> inline bool operator <= (ArbInt     const& l, T          const  r) { return  l.op_le(r); }
  template <class T> inline bool operator <= (T          const  l, ArbInt     const& r) { return !r.op_lt(l); }
                     inline bool operator == (ArbInt     const& l, ArbInt     const& r) { return  l.op_eq(r); }
  template <class T> inline bool operator == (ArbInt     const& l, SafeInt<T> const  r) { return  l.op_eq(r); }
  template <class T> inline bool operator == (SafeInt<T> const  l, ArbInt     const& r) { return  r.op_eq(l); }
  template <class T> inline bool operator == (ArbInt     const& l, T          const  r) { return  l.op_eq(r); }
  template <class T> inline bool operator == (T          const  l, ArbInt     const& r) { return  r.op_eq(l); }
                     inline bool operator != (ArbInt     const& l, ArbInt     const& r) { return  l.op_ne(r); }
  template <class T> inline bool operator != (ArbInt     const& l, SafeInt<T> const  r) { return  l.op_ne(r); }
  template <class T> inline bool operator != (SafeInt<T> const  l, ArbInt     const& r) { return  r.op_ne(l); }
  template <class T> inline bool operator != (ArbInt     const& l, T          const  r) { return  l.op_ne(r); }
  template <class T> inline bool operator != (T          const  l, ArbInt     const& r) { return  r.op_ne(l); }
  
  // Bitwise operators.
                     inline ArbInt operator & (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_bit_and(r); }
  template <class T> inline ArbInt operator & (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_bit_and(r); }
  template <class T> inline ArbInt operator & (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(r).op_bit_and(l); }
  template <class T> inline ArbInt operator & (ArbInt     const& l, T          const  r) { return ArbInt(l).op_bit_and(r); }
  template <class T> inline ArbInt operator & (T          const  l, ArbInt     const& r) { return ArbInt(r).op_bit_and(l); }
                     inline ArbInt operator | (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_bit_ior(r); }
  template <class T> inline ArbInt operator | (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_bit_ior(r); }
  template <class T> inline ArbInt operator | (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(r).op_bit_ior(l); }
  template <class T> inline ArbInt operator | (ArbInt     const& l, T          const  r) { return ArbInt(l).op_bit_ior(r); }
  template <class T> inline ArbInt operator | (T          const  l, ArbInt     const& r) { return ArbInt(r).op_bit_ior(l); }
                     inline ArbInt operator ^ (ArbInt     const& l, ArbInt     const& r) { return ArbInt(l).op_bit_xor(r); }
  template <class T> inline ArbInt operator ^ (ArbInt     const& l, SafeInt<T> const  r) { return ArbInt(l).op_bit_xor(r); }
  template <class T> inline ArbInt operator ^ (SafeInt<T> const  l, ArbInt     const& r) { return ArbInt(r).op_bit_xor(l); }
  template <class T> inline ArbInt operator ^ (ArbInt     const& l, T          const  r) { return ArbInt(l).op_bit_xor(r); }
  template <class T> inline ArbInt operator ^ (T          const  l, ArbInt     const& r) { return ArbInt(r).op_bit_xor(l); }
  
}

#endif
