/*****************************************************************************
 * Arb.hxx
 *****************************************************************************
 * Interface for class Arb.
 *****************************************************************************/

// Include guard.
#if !defined(ARB_43693478di8u7do)
  #define ARB_43693478di8u7do
  
  // STL includes.
  #include <iostream>
  #include <string>
  #include <vector>
  #include <algorithm>
  
  // Internal includes.
  #include "SafeInteger/SafeInteger.hxx"
  #include "ReferencePointer.hxx"
  #include "rppower.hxx"
  #include "toString.hxx"
  
  // Namespace wrapping.
  namespace DAC {
    
    /*********************************************************************
      * ArbInt
      *********************************************************************
      * This is an integer of an arbitrary number of digits.
      *********************************************************************/
    template <class T> class ArbInt {
      
      /*
        * Public members.
        */
      public:
        
        /*****************************************************************/
        // Typedefs.
        
        typedef T value_type;
        
        /*****************************************************************/
        // Function members.
        
        // Default constructor.
        ArbInt ();
        
        // Copy constructor.
        ArbInt (ArbInt const& number);
        
        // Conversion constructor.
                            ArbInt (std::string const& number);
        template <class FT> ArbInt (FT          const  number);
        
        // Reset to just-constructed state.
        ArbInt& clear ();
        
        // Assignment operator.
        ArbInt& operator = (std::string const& number);
        ArbInt& operator = (ArbInt      const& number);
        
        // Arithmetic assignment operators.
        ArbInt& operator *= (ArbInt const& number);
        ArbInt& operator /= (ArbInt const& number);
        ArbInt& operator -= (ArbInt const& number);
        
        // Accessors.
        T       Base ()             const;
        ArbInt& Base (T const base);
        
        // Set this number with a string.
                            ArbInt<T>& set (std::string const& number, T const base = 0);
                            ArbInt<T>& set (ArbInt      const& number);
        template <class FT> ArbInt<T>& set (FT          const  number);
        
        // Return a string of this number.
        std::string toString (T const base = 0) const;
        
        // Arithmetic operator backends.
        ArbInt& op_mul (ArbInt const& number);
        ArbInt& op_div (ArbInt const& number, ArbInt* remainder = 0);
        ArbInt& op_add (ArbInt const& number);
        ArbInt& op_sub (ArbInt const& number);
        
        // Comparison operator backends.
        bool op_gt (ArbInt const& number) const;
        
        // Raise this number to a power.
        ArbInt& pow (ArbInt const& exp);
      
      /*
        * Private members.
        */
      private:
        
        /*****************************************************************/
        // Typedefs.
        
        typedef char          _StrChrT; // String character.
        typedef unsigned char _NumChrT; // Numeric character.
        typedef T             _DigT;    // Native digit.
        
        typedef std::vector<_NumChrT> _DigStrT; // String of character
                                                // digits.
        typedef std::vector<_DigT>    _DigsT;   // String of native
                                                // digits.
        
        typedef ReferencePointer<_DigsT> _DataPT; // Pointer to data.
        
        /*****************************************************************/
        // Data members.
        
        // The number.
        _DataPT _digits;
        
        // The default base of this number.
        T _base;
        
        /*****************************************************************/
        // Static data members.
        
        static bool s_initialized;
        
        static int   s_digitbits; // Number of bits in a digit.
        static _DigT s_digitbase; // Base of native digits.
        
        static _NumChrT s_numdigits; // Number of output digits.
        static _StrChrT s_odigits[]; // Output digits.
        
        static std::vector<_NumChrT> s_idigits; // Input digits.
        
        /*****************************************************************/
        // Function members.
        
        // Common initialization tasks.
        void _init ();
        
        // Perform carry or borrow.
        ArbInt& _carry  (typename _DigsT::size_type start);
        ArbInt& _borrow (typename _DigsT::size_type start);
        
        // Trim insignificant zeros.
        ArbInt& _trimZeros ();
        
        /*****************************************************************/
        // Static function members.
        
        // Class initialization.
        static bool s_classInit () throw();
        
        // Trim zeros from a given container.
        template <class CT> static void s_trimZerosB (CT& c);
        template <class CT> static void s_trimZerosE (CT& c);
        template <class CT> static void s_trimZeros  (CT& c);
        
        // Do long division on a given container. Returns the remainder.
        template <class DivndT, class DivorT> static DivorT s_longDiv (DivndT& divnd, DivorT const divor, T const base);
        
        // Convert a container from one base to another.
        template <class FT, class TT> static void s_baseConv (FT const& from, T const frombase, TT& to, T const tobase);
      
    };
    
    /*************************************************************************
     * Arb
     *************************************************************************
     * This is an arbitrary precision number class.
     *************************************************************************/
    class Arb {
      
      /*
       * Private members.
       */
      private:
        
        /*********************************************************************/
        // Typedefs.
        
        // Native digit type. Setting this to a larger type will allow larger
        // numbers to be stored, however they will be slower and take up more
        // memory. Setting this to a smaller type will restrict Arb to smaller
        // numbers and use less memory, but not likely have an effect on
        // speed. This must be an unsigned integer type, that is, char, short,
        // int, long, and sometimes long long.
        typedef unsigned int _DigT;
        
      /*
       * Public members.
       */
      public:
        
        /*********************************************************************/
        // Typedefs.
        
        // This is the type that controls where the radix point is in a fixed
        // decimal number.
        typedef _DigT PointPosT;
        
        /*********************************************************************/
        // Function members.
        
        // Default constructor.
        Arb ();
        
        // Destructor.
        ~Arb ();
        
        // Reset to just-constructed defaults.
        Arb& clear ();
        
        // Convert to string.
        std::string toString () const;
        
        // Set the number.
        Arb& set (std::string const& number, PointPosT const decimal = 0, bool const fix = false);
      
      /*
       * Private members.
       */
      private:
        
        /*********************************************************************/
        // Typedefs.
        
        // Forward declarations.
        class _Data;
        
        typedef ArbInt<_DigT> _DigsT; // Native digits type.
        
        typedef ReferencePointer<_Data> _DataPT; // Pointer to number data.
        
        /*********************************************************************/
        // Data types.
        
        /*********************************************************************
         * _Data
         *********************************************************************
         * This holds all data for this number, copying this data structure to
         * another number will make a perfect copy of this number.
         *********************************************************************/
        class _Data {
          
          /*
           * Public members.
           */
          public:
            
            /*****************************************************************/
            // Data members.
            
            bool positive; // True if the number is positive.
            
            _DigsT p;        // Numerator.
            _DigsT q;        // Denominator.
            
            PointPosT pointpos; // Radix point position.
            bool      fix;      // If true, fix the radix point.
            
            _DigT origbase; // Original base of this number.
            
            /*****************************************************************/
            // Function members.
            
            // Default constructor.
            _Data ();
            
            // Reset to just-constructed state.
            _Data& clear ();
            
          /*
           * Private members.
           */
          private:
            
            /*****************************************************************/
            // Function members.
            
            // Common initialization routines.
            void _init ();
          
        };
        
        /*********************************************************************/
        // Data members.
        
        // The number.
        _DataPT _data;
        
        /*********************************************************************/
        // Function members.
        
        // Common initialization tasks.
        void _init ();
        
        /*********************************************************************/
        // Static function members.
        
        /*
        // Do long division or multiplication on a given container. Container
        // must be little-endian for division, big-endian for multiplication.
        // These are grouped because they both involve applying one number to
        // a container, but semantics of each are very different.
        template <class LT,     class RT>     static ReferencePointer<LT> s_longMul (LT const& l, RT const r);
        
        // Perform integer arithmetic on two big-endian containers.
        // Subtraction requires that minuend be greater than or equal to
        // the subtrahend. Base is 2^(bits/2).
        template <class T> static ReferencePointer<T> s_intMul (T const& mulnd, T const& mulor);
        template <class T> static ReferencePointer<T> s_intDiv (T const& divor, T const& divnd, ReferencePointer<T> remainder = 0);
        template <class T> static ReferencePointer<T> s_intAdd (T const& aug,   T const& add);
        template <class T> static ReferencePointer<T> s_intSub (T const& min,   T const& sub);
        template <class T> static ReferencePointer<T> s_intPow (T const& base,  T const& expn);
        
        // Get the greatest common divisor and least common multiple of two
        // big-endian containers. Base is 2^(bits/2).
        template <class T> static ReferencePointer<T> s_gcd (T const& c1, T const& c2);
        template <class T> static ReferencePointer<T> s_lcm (T const& c1, T const& c2);
        
        // Perform a carry on a big-endian container. Base is 2^(bits/2).
        template <class T> static void s_carry  (T& c, typename T::size_type const start);
        template <class T> static void s_borrow (T& c, typename T::size_type const start);
        
        // Comparison operators on containers.
        template <class T> static bool s_lt (T const& l, T const& r);
        template <class T> static bool s_le (T const& l, T const& r);
        template <class T> static bool s_gt (T const& l, T const& r);
        template <class T> static bool s_ge (T const& l, T const& r);
        template <class T> static bool s_eq (T const& l, T const& r);
        template <class T> static bool s_ne (T const& l, T const& r);
        */
      
    };
    
  };
  
  /***************************************************************************
   * Global operators.
   ***************************************************************************/
  
  // Stream I/O operators.
                     std::ostream& operator << (std::ostream& l, DAC::Arb       const& r);
  template <class T> std::ostream& operator << (std::ostream& l, DAC::ArbInt<T> const& r);
                     std::istream& operator >> (std::istream& l, DAC::Arb&             r);
  template <class T> std::istream& operator >> (std::istream& l, DAC::ArbInt<T>&       r);
  
  // Arithmetic operators.
  template <class T> DAC::ArbInt<T> operator * (DAC::ArbInt<T> const& l, DAC::ArbInt<T> const& r);
  
  // Comparison operators.
  template <class T> bool operator > (DAC::ArbInt<T> const& l, DAC::ArbInt<T> const& r);
  
  /***************************************************************************
   * Error declarations.
   ***************************************************************************/
  namespace DAC {
    
    // Errors.
    namespace ArbErrors {
      class Base      : public Exception { public: virtual char const* what () const throw(); };
      class BadFormat : public Base      {
        public:
          virtual char const* what () const throw();
          virtual BadFormat& Problem  (char const*                   const problem)  throw();
          virtual BadFormat& Position (std::string::size_type        const position) throw();
          virtual BadFormat& Number   (ConstReferencePointer<std::string>& number)   throw();
        protected:
          char const* _problem;
          std::string::size_type _position;
          ConstReferencePointer<std::string> _number;
      };
    };
    
    namespace ArbIntErrors {
      class Base            : public ArbErrors::Base  { public: virtual char const* what () const throw(); };
      class BadFormat       : public Base             {
        public:
          virtual char const* what () const throw();
          virtual BadFormat& Problem  (char const*                   const problem)  throw();
          virtual BadFormat& Position (std::string::size_type        const position) throw();
          virtual BadFormat& Number   (ConstReferencePointer<std::string>& number)   throw();
        protected:
          char const* _problem;
          std::string::size_type _position;
          ConstReferencePointer<std::string> _number;
      };
      class ClassInitFailed : public Base             { public: virtual char const* what () const throw(); };
      class Negative        : public Base             { public: virtual char const* what () const throw(); };
      class Overrun         : public Base             { public: virtual char const* what () const throw(); };
    };
    
  };
    
  /***************************************************************************
   * Inline and template definitions.
   ***************************************************************************/
  namespace DAC {
    
    // Errors.
    namespace ArbErrors {
      inline char const* Base::what          () const throw() { return "Undefined error in Arb.";                                                                                                                                            }
      inline char const* BadFormat::what     () const throw() { return (std::string(_problem) + " at position " + DAC::toString((SafeInteger<std::string::size_type>(_position) + 1).Value()) + " in number \"" + *_number + "\".").c_str(); }
      inline BadFormat&  BadFormat::Problem  (char const*                   const problem)  throw() { _problem  = problem;  return *this; }
      inline BadFormat&  BadFormat::Position (std::string::size_type        const position) throw() { _position = position; return *this; }
      inline BadFormat&  BadFormat::Number   (ConstReferencePointer<std::string>& number)   throw() { _number   = number;   return *this; }
    };
    
    namespace ArbIntErrors {
      inline char const* Base::what            () const throw() { return "Undefined error in ArbInt.";                                                                                                                                   }
      inline char const* BadFormat::what       () const throw() { return (std::string(_problem) + " at position " + DAC::toString((SafeInteger<std::string::size_type>(_position) + 1).Value()) + " in number \"" + *_number + "\".").c_str(); }
      inline BadFormat&  BadFormat::Problem    (char const*                   const problem)  throw() { _problem  = problem;  return *this; }
      inline BadFormat&  BadFormat::Position   (std::string::size_type        const position) throw() { _position = position; return *this; }
      inline BadFormat&  BadFormat::Number     (ConstReferencePointer<std::string>& number)   throw() { _number   = number;   return *this; }
      inline char const* ClassInitFailed::what () const throw() { return "Class initialization of ArbInt failed.";                                                                                                                       }
      inline char const* Negative::what        () const throw() { return "Attempted to set ArbInt to a negative number.";                                                                                                                }
      inline char const* Overrun::what         () const throw() { return "Instruction overruns end of container.";                                                                                                                             }
    };
    
    /*************************************************************************
     * Class Arb.
     *************************************************************************/
    
    /*
    // Get the greatest common divisor of two big-endian containers. Base
    // is 2^(bits/2).
    template <class T> ReferencePointer<T> Arb::s_gcd (T const& c1, T const& c2) {
      
      // Return value.
      ReferencePointer<T> retval(new T);
      
      // Work area.
      T tmp_c1(c1);
      T tmp_c2(c2);
      if (s_lt(tmp_c1, tmp_c2)) {
        tmp_c1.swap(tmp_c2);
      }
      
      // Euclid's algorithm.
      while (tmp_c2 != 0) {
        T                   tmp = tmp_c2;
        ReferencePointer<T> remainder(new T);
        s_intDiv(tmp_c1, tmp_c2, remainder);
        tmp_c2.swap(*remainder);
        tmp_c1.swap(tmp);
      }
      
      // Swap in result and return.
      retval->swap(tmp_c1);
      return retval;
      
    }
    
    // Get the least common multiple of two big-endian containers. Base is
    // 2^(bits/2).
    template <class T> ReferencePointer<T> Arb::s_lcm (T const& c1, T const& c2) {
      
      // Return value.
      ReferencePointer<T> retval(new T);
      
      // Work area.
      T tmp_c1(c1);
      T tmp_c2(c2);
      if (s_lt(tmp_c1, tmp_c2)) {
        tmp_c1.swap(tmp_c2);
      }
      
      // LCM is (c1 * c2) / gcd(c1, c2). c1 is always the largest of the two,
      // save the multiplication by c1 until the end when we have the smallest
      // number possible.
      return s_intMul(*s_intDiv(tmp_c2, s_gcd(tmp_c1, tmp_c2)), tmp_c1);
      
    }
    */
    
    /*************************************************************************
     * Class ArbInt.
     *************************************************************************/
    
    /*************************************************************************/
    // Static member initialization.
    
    template <class T> int                       ArbInt<T>::s_digitbits = 0;
    template <class T> typename ArbInt<T>::_DigT ArbInt<T>::s_digitbase = 0;
    
    template <class T> typename ArbInt<T>::_NumChrT ArbInt<T>::s_numdigits = 36;
    template <class T> typename ArbInt<T>::_StrChrT ArbInt<T>::s_odigits[] = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
      'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
      'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    template <class T> std::vector<typename ArbInt<T>::_NumChrT> ArbInt<T>::s_idigits;
    
    // Call class constructor.
    template <class T> bool ArbInt<T>::s_initialized = s_classInit();
    
    /*************************************************************************/
    // Function members.
    
    // Default constructor.
    template <class T> ArbInt<T>::ArbInt () {
      
      // Call common init.
      _init();
      
    }
    
    // Copy constructor.
    template <class T> ArbInt<T>::ArbInt (ArbInt<T> const& number) {
      
      // Call common init.
      _init();
      
      // Set the number.
      set(number);
      
    }
    
    // Conversion constructor.
    template <class T> ArbInt<T>::ArbInt (std::string const& number) {
      
      // Call common init.
      _init();
      
      // Set the number.
      set(number, 0);
      
    }
    template <class T> template <class FT> ArbInt<T>::ArbInt (FT const number) {
      
      // Call common init.
      _init();
      
      // Set the number.
      set<FT>(number);
      
    }
    
    // Assignment operator.
    template <class T> inline ArbInt<T>& ArbInt<T>::operator = (std::string const& number) { return set(number, 0); }
    template <class T> inline ArbInt<T>& ArbInt<T>::operator = (ArbInt<T>   const& number) { return set(number);    }
    
    // Arithmetic assignment operators.
    template <class T> inline ArbInt<T>& ArbInt<T>::operator *= (ArbInt<T> const& number) { return op_mul(number); }
    template <class T> inline ArbInt<T>& ArbInt<T>::operator /= (ArbInt<T> const& number) { return op_div(number); }
    template <class T> inline ArbInt<T>& ArbInt<T>::operator -= (ArbInt<T> const& number) { return op_sub(number); }
    
    // Reset to just-constructed state.
    template <class T> ArbInt<T>& ArbInt<T>::clear () {
      
      // Create a new vector, this preserves COW behavior.
      _digits = new _DigsT;
      
      // Reset the default base.
      _base = 10;
      
      // Return self.
      return *this;
      
    }
    
    // Returns or sets the default base of this number.
    template <class T> inline T          ArbInt<T>::Base ()             const { return _base;               }
    template <class T> inline ArbInt<T>& ArbInt<T>::Base (T const base)       { _base = base; return *this; }
    
    // Set this number with a string.
    template <class T> ArbInt<T>& ArbInt<T>::set (std::string const& number, T const base) {
      
      // Load the number into this for exception safety and COW.
      _DataPT new_digits(new _DigsT);
      
      // Hold the number in case an error needs to be thrown.
      ConstReferencePointer<std::string> tmp_number(new std::string(number));
      
      // Get the base of this number. Use the default base if none was supplied.
      T numbase = base;
      if (numbase == 0) {
        numbase = _base;
      }
      
      // Parser will load data into here.
      _DigStrT num;
      
      // Parse the number.
      for (typename std::string::size_type i = 0; i != number.length(); ++i) {
        
        // Get the value of this digit.
        _NumChrT digval = s_idigits[number[i]];
        
        // Make sure this digit is within the number base.
        if ((digval >= SafeInteger<T>(numbase).Value() || (digval == std::numeric_limits<_NumChrT>::max()))) {
          throw ArbIntErrors::BadFormat().Problem("Unrecognized character").Position(i).Number(tmp_number);
        }
        
        // Add the digit to the digit string.
        num.insert(num.begin(), digval);
        
      }
      
      // Trim insignificant zeros. This number is little-endian at this point.
      s_trimZerosE(num);
      
      // Convert to the native number base.
      s_baseConv(num, numbase, *new_digits, s_digitbase);
      
      // The new number has been loaded successfully. Swap it in.
      _digits = new_digits;
      
      // We done, return the new number.
      return *this;
      
    }
    
    // Set this number from another ArbInt.
    template <class T> ArbInt<T>& ArbInt<T>::set (ArbInt<T> const& number) {
      
      // Make another reference to the number. ArbInt is COW, so the actual
      // copy will wait until a change is made.
      _digits = number._digits;
      
      // That's it.
      return *this;
      
    }
    
    // Set this number from another number.
    template <class T> template <class FT> ArbInt<T>& ArbInt<T>::set (FT const number) {
      
      // Work area.
      _DataPT new_digits(new _DigsT);
      
      // Only something to set if the number is not zero.
      if (number != 0) {
        
        // If number is less than zero, throw an error.
        if (number < 0) {
          throw ArbIntErrors::Negative();
        }
        
        // Convert with repeated division.
        SafeInteger<FT> tmp_number(number);
        while (tmp_number > 0) {
          new_digits->push_back((tmp_number % s_digitbase).Value());
          tmp_number /= s_digitbase;
        }
        
      }
      
      // Swap in the new digits and return.
      _digits = new_digits;
      return *this;
      
    }
    
    // Return a string of this number.
    template <class T> std::string ArbInt<T>::toString (T const base) const {
      
      // This is the string we will return.
      std::string retval;
      
      // Easy case of 0.
      if (_digits->size() == 0) {
        
        retval = "0";
        
      // Otherwise we have work to do.
      } else {
        
        // Get the base of this number. Use the default base if none was supplied.
        T numbase = base;
        if (numbase == 0) {
          numbase = _base;
        }
        
        // Convert to the output base.
        _DigStrT num;
        s_baseConv(*_digits, s_digitbase, num, numbase);
        std::cout << "num.size(): " << num.size() << "  _digits->size(): " << _digits->size() << std::endl;
        
        // Load this into the string. If the base is greater than th enumber
        // of digits defined, output the raw numbers of each digit.
        if (SafeInteger<T>(base) > s_numdigits) {
          for (typename _DigStrT::reverse_iterator i = num.rbegin(); i != num.rend(); ++i) {
            retval += "'" + DAC::toString(*i) + "'";
            if (i != (num.rend() - 1)) {
              retval += ",";
            }
          }
        } else {
          for (typename _DigStrT::reverse_iterator i = num.rbegin(); i != num.rend(); ++i) {
            std::cout "*i: " << *i << std::endl;
            retval += s_odigits[*i];
          }
        }
        
      }
      
      // String constructed, return it.
      std::cout << "retval: " << retval << std::endl;
      return retval;
      
    }
    
    // Multiply.
    template <class T> ArbInt<T>& ArbInt<T>::op_mul (ArbInt<T> const& number) {
      
      // Work area.
      ArbInt<T> retval;
      
      // If either number is zero, no multiplying to be done.
      if ((_digits->size() != 0) && (number._digits->size() != 0)) {
        
        // Create a digit product and make a reference its digits to reduce
        // typing.
        ArbInt<T> digproduct;
        _DigsT& dpd = *(digproduct._digits);
        
        // Multiply like 3rd grade.
        for (typename _DigsT::size_type i = 0; i != _digits->size(); ++i) {
          
          // Get the product for a single digit.
          for (typename _DigsT::size_type j = 0; j != number._digits->size(); ++j) {
            
            // Create a new digit in the digit product if necessary.
            if (dpd.size() == j) {
              dpd.push_back(0);
            }
            
            // Multiply into the digit product and carry.
            dpd[j] = (SafeInteger<_DigT>(dpd[j]) + SafeInteger<_DigT>((*_digits)[i]) * SafeInteger<_DigT>((*(number._digits))[j])).Value();
            digproduct._carry(j);
            
          }
          
          // Offset this digit product and add it to the final product.
          digproduct._digits->insert(digproduct._digits->begin(), i, 0);
          retval.op_add(digproduct);
          
        }
        
      }
      
      // Swap in the result and return.
      _digits = retval._digits;
      return *this;
      
    }
    
    // Divide.
    template <class T> ArbInt<T>& ArbInt<T>::op_div (ArbInt<T> const& number, ArbInt<T>* remainder) {
      
      // Work area
      ArbInt<T> retval;
      
      // If number > this, result is zero, remainder is this.
      if (number > *this) {
        
        // Set the remainder.
        if (remainder != 0) {
          *remainder = *this;
        }
        
      // Otherwise we have work to do.
      } else {
        
        // Cache a copy of the high-order digit of the dividend.
        SafeInteger<_DigT> roughdivnd = number._digits->back();
        
        // Seed the group of digits we will be dividing, then iterate through
        // the divisor.
        ArbInt<T> diggroup;
        ArbInt<T> test;
        *(diggroup._digits) = _DigsT(_digits->rbegin(), _digits->rbegin() + number._digits->size());
        for (typename _DigsT::reverse_iterator i = _digits->rbegin() + number._digits->size(); i != _digits->rend(); ++i) {
          
          // Make a guess at the quotient of this digit by dividing the high-
          // order digits.
          SafeInteger<_DigT> guess = diggroup._digits->back() / roughdivnd;
          
          // Correct the guess.
          test = *this * ArbInt<T>(guess.Value());
          if (test > diggroup) {
            test = *this * ArbInt<T>((--guess).Value());
          } else {
            test = *this * ArbInt<T>((++guess).Value());
          }
          
          // The guess must be correct by this point. Add it to th quotient
          // and prepare for the next iteration.
          retval._digits->insert(retval._digits->begin(), guess.Value());
          diggroup -= test;
          
        }
        
        // Set the remainder if a container was given.
        if (remainder != 0) {
          *remainder = diggroup;
        }
        
      }
      
      // Clean up, move the result into place and return.
      retval._trimZeros();
      _digits = retval._digits;
      return *this;
      
    }
    
    // Add.
    template <class T> ArbInt<T>& ArbInt<T>::op_add (ArbInt<T> const& number) {
      
      // Work area.
      ArbInt<T> retval(*this);
      
      // Add like kindergarten.
      for (typename _DigsT::size_type i = 0; i != number._digits->size(); ++i) {
        
        // Create a new digit if necessary.
        if (i == retval._digits->size()) {
          retval._digits->push_back(0);
        }
        
        // Add this digit and carry.
        (*(retval._digits))[i] = (SafeInteger<_DigT>((*(retval._digits))[i]) + SafeInteger<_DigT>((*(number._digits))[i])).Value();
        retval._carry(i);
        
      }
      
      // Move the result into place and return.
      _digits = retval._digits;
      return *this;
      
    }
    
    // Subtract.
    template <class T> ArbInt<T>& ArbInt<T>::op_sub (ArbInt<T> const& number) {
      
      // Work area.
      ArbInt<T> retval(*this);
      
      // These are unsigned numbers, so if number > this, throw an error.
      if (number > retval) {
        throw ArbIntErrors::Negative();
      }
      
      // Subtract like kindergarten.
      for (typename _DigsT::size_type i = 0; i != number._digits->size(); ++i) {
        
        // Borrow if necessary and subtract.
        if ((*(retval._digits))[i] < (*(number._digits))[i]) {
          retval._borrow(i);
        }
        (*(retval._digits))[i] = (SafeInteger<_DigT>((*(retval._digits))[i]) - SafeInteger<_DigT>((*(number._digits))[i])).Value();
        
      }
      
      // Trim zeros.
      retval._trimZeros();
      
      // Move the result into place and return.
      _digits = retval._digits;
      return *this;
      
    }
    
    // Greater than.
    template <class T> bool ArbInt<T>::op_gt (ArbInt<T> const& number) const {
      
      // Check sizes of containers first.
      if (_digits->size() > number._digits->size()) {
        return true;
      }
      if (_digits->size() < number._digits->size()) {
        return false;
      }
      if ((_digits->size() == 0) && (number._digits->size() == 0)) {
        return false;
      }
      
      // Step through each element looking for a difference, start at high-
      // order and work down.
      for (typename _DigsT::size_type i = 0; i != _digits->size(); ++i) {
        typename _DigsT::size_type j = (_digits->size() - 1) - i;
        if ((*(_digits))[j] > (*(number._digits))[j]) {
          return true;
        }
        if ((*(_digits))[j] < (*(number._digits))[j]) {
          return false;
        }
      }
      
      // No difference was found, is not greater.
      return false;
      
    }
    
    // Raise this number to a power.
    template <class T> ArbInt<T>& ArbInt<T>::pow (ArbInt<T> const& exp) {
      
      // Work area.
      ArbInt<T> tmp_base(*this);
      ArbInt<T> tmp_expn(exp);
      ArbInt<T> retval(1);
      
      // Russian peasant power.
      while (tmp_expn._digits->size() > 0) {
        if (tmp_expn._digits->front() & 1) {
          retval *= tmp_base;
        }
        tmp_base *= tmp_base;
        tmp_expn /= ArbInt<T>(2);
      }
      
      std::cout << "base: " << *this << "  expn: " << exp << "  result: " << retval << std::endl;
      
      // Set the result and return.
      _digits = retval._digits;
      return *this;
      
    }
    
    // Common initialization tasks.
    template <class T> void ArbInt<T>::_init () {
      
      // Check that the class constructor was successfully called.
      if (!s_initialized) {
        throw ArbIntErrors::ClassInitFailed();
      }
      
      // Clear.
      clear();
      
    }
    
    // Perform carry. Only call this on temporary objects that are not copied.
    // Copy on write is not preserved for this function.
    template <class T> ArbInt<T>& ArbInt<T>::_carry (typename _DigsT::size_type start) {
      
      // Ensure that the start is not beyond the end of the container.
      if (start >= _digits->size()) {
        throw ArbIntErrors::Overrun();
      }
      
      // Loop through the container looking for base overflow.
      for (typename _DigsT::size_type i = start; i != _digits->size(); ++i) {
        
        // If we find overflow, push it to the next digit.
        if ((*_digits)[i] >= s_digitbase) {
          
          // Create the next digit if it does not already exist.
          if ((_digits->size() - 1) <= i) {
            _digits->push_back(0);
          }
          
          // Add any overflow to the next digit and remove it from the current
          // digit. No need to check i + 1 for overflow; i is the size_type of
          // _DigsT, and we just added an element, we would have recieved an
          // error when we did that.
          SafeInteger<typename _DigsT::value_type> overflow = SafeInteger<typename _DigsT::value_type>((*_digits)[i]) / s_digitbase;
          (*_digits)[i + 1]                                 = (SafeInteger<typename _DigsT::value_type>((*_digits)[i + 1]) + overflow).Value();
          (*_digits)[i]                                     = (SafeInteger<typename _DigsT::value_type>((*_digits)[i]) - (overflow * s_digitbase)).Value();
          
        // If there is no overflow now, there will be no more overflow.
        } else {
          
          // Simply leave the loop.
          break;
          
        }
        
      }
      
    }
    
    // Perform borrow. Only call this on temporary objects that are not
    // copied. Copy on write is not preserved for this function.
    template <class T> ArbInt<T>& ArbInt<T>::_borrow (typename _DigsT::size_type start) {
      
      // Ensure that the start is not beyond the end of the container.
      if (start >= _digits->size()) {
        throw ArbIntErrors::Overrun();
      }
      
      // Loop through the container borrowing until we've met our borrow.
      for (typename _DigsT::size_type i = start; i != (_digits->size() - 1); ++i) {
        
        // Add base to this digit.
        (*_digits)[i] = (SafeInteger<_DigT>((*_digits)[i]) + s_digitbase).Value();
        
        // If the next digit is > 0, subtract 1 and we're done.
        if ((*_digits)[i + 1] > 0) {
          --(*_digits)[i + 1];
          _trimZeros();
          return *this;
        }
        
      }
      
      // If we get here, we have not paid for our borrow.
      throw ArbIntErrors::Overrun();
      
    }
    
    // Trim insignificant zeros.
    template <class T> inline ArbInt<T>& ArbInt<T>::_trimZeros () {
      
      // Trim zeros and return.
      s_trimZerosE(*_digits);
      return *this;
      
    }
    
    // Class constructor.
    template <class T> bool ArbInt<T>::s_classInit () throw() {
      
      // This cannot throw.
      try {
        
        // Get the maximum number that can be held in a single digit.
        s_digitbits = std::numeric_limits<_DigT>::digits >> 1;
        s_digitbase = rppower(_DigT(2), s_digitbits);
        
        // Get the input digits.
        SafeInteger<_NumChrT> j;
        for (_NumChrT i = 0; i != std::numeric_limits<_NumChrT>::max(); ++i) {
          j = i;
          SafeInteger<_NumChrT> digit;
          if      ((j >= '0') && (j <= '9')) { digit = j - '0';                         }
          else if ((j >= 'A') && (j <= 'Z')) { digit = j - 'A' + 10;                    }
          else if ((j >= 'a') && (j <= 'z')) { digit = j - 'a' + 10;                    }
          else                               { digit = std::numeric_limits<_NumChrT>::max(); }
          s_idigits.push_back(digit.Value());
        }
        
      } catch (...) {
        
        // If any exception was caught, we failed. Have fun debugging.
        return false;
        
      }
      
      // Happy joy.
      return true;
      
    }
    
    // Trim leading zeros from a given container.
    template <class T> template <class CT> void ArbInt<T>::s_trimZerosB (CT& c) {
      
      // Nothing to do if empty.
      if (!c.empty()) {
        
        // Work data.
        typename CT::iterator pos;
        
        // Trim leading zeros.
        for (pos = c.begin(); (pos != c.end()) && (*pos == 0); ++pos) {}
        if (pos >= c.begin()) {
          c.erase(c.begin(), pos);
        }
        
      }
      
    }
    
    // Trim trailing zeros from a given container.
    template <class T> template <class CT> void ArbInt<T>::s_trimZerosE (CT& c) {
      
      // Nothing to do if empty.
      if (!c.empty()) {
        
        // Work data.
        typename CT::iterator pos;
        
        // Trim trailing zeros.
        for (pos = (c.end() - 1); (pos != (c.begin() - 1)) && (*pos == 0); --pos) {}
        if (pos++ < (c.end() - 1)) {
          c.erase(pos, c.end());
        }
        
      }
      
    }
    
    // Trim leading and trailing zeros from a given container.
    template <class T> template <class CT> void ArbInt<T>::s_trimZeros (CT& c) { s_trimZerosB(c); s_trimZerosE(c); }
    
    // Do long division on a given container in the specified base.
    template <class T> template <class DivndT, class DivorT> DivorT ArbInt<T>::s_longDiv (DivndT& divnd, DivorT const divor, T const base) {
      
      // Group of digits to divide.
      SafeInteger<DivorT> dgroup;
      SafeInteger<DivorT> dquot;
      
      // Quotient.
      DivndT quotient;
      
      // Long division steps through each digit of the dividend.
      for (typename DivndT::reverse_iterator i = divnd.rbegin(); i != divnd.rend(); ++i) {
        
        // Add this digit to the group.
        dgroup += *i;
        
        // Divide the group and add the result to the quotient.
        dquot = dgroup / divor;
        quotient.insert(quotient.begin(), dquot.Value());
        
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
      return SafeInteger<DivorT>((dgroup / base).Value()).Value();
      
    }
    
    // Convert a container from one base to another.
    template <class T> template <class FT, class TT> void ArbInt<T>::s_baseConv (FT const& from, T const frombase, TT& to, T const tobase) {
      
      // Empty out target container.
      to.clear();
      
      // Temporary, since work will be done in place.
      FT tmp_from(from);
      
      // Convert base by storing the remainder of repeated division by the
      // base that we will be converting to, in the base that we are
      // converting from. Least significant digits come out first.
      while (tmp_from.size() > 0) {
        to.push_back(SafeInteger<typename TT::value_type>(s_longDiv(tmp_from, tobase, frombase)).Value());
      }
      
    }
    
  };
  
  /***************************************************************************
   * Inline and template definitions.
   ***************************************************************************/
  
  // Stream I/O operators.
                     inline std::ostream& operator << (std::ostream& l, DAC::Arb       const& r) { l << r.toString();                                  return l; }
  template <class T> inline std::ostream& operator << (std::ostream& l, DAC::ArbInt<T> const& r) { l << r.toString(0);                                 return l; }
                     inline std::istream& operator >> (std::istream& l, DAC::Arb&             r) { std::string input; std::cin >> input; r.set(input); return l; }
  template <class T> inline std::istream& operator >> (std::istream& l, DAC::ArbInt<T>&       r) { std::string input; std::cin >> input; r.set(input); return l; }
  
  // Arithmetic operators.
  template <class T> inline DAC::ArbInt<T> operator * (DAC::ArbInt<T> const& l, DAC::ArbInt<T> const& r) { DAC::ArbInt<T> retval(l); return retval.op_add(r); }
  
  // Comparison operators.
  template <class T> inline bool operator > (DAC::ArbInt<T> const& l, DAC::ArbInt<T> const& r) { DAC::ArbInt<T> retval(l); return retval.op_gt(r); }
  
#endif
