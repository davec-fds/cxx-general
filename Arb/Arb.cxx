/*****************************************************************************
 * Arb.cxx
 *****************************************************************************
 * Implementation for class Arb.
 *****************************************************************************/

// STL includes.
#include <string>
#include <algorithm>
#include <iostream> // FIXME: For debugging only.

// Internal includes.
#include "rppower.hxx"
#include "toString.hxx"
#include "reduce.hxx"

// Class include.
#include "Arb.hxx"

// Namespaces used.
using namespace std;

// Namespace wrapper.
namespace DAC {
  
  /***************************************************************************
   * Class Arb.
   ***************************************************************************/
  
  /***************************************************************************/
  // Function members.
  
  // Default constructor.
  Arb::Arb () {
    
    // Call common init.
    _init();
    
  }
  
  // Copy constructor.
  Arb::Arb (Arb const& number, bool const copynow) {
    
    // Call common init.
    _init();
    
    // Set the number.
    copy(number, copynow);
    
  }
  
  // Conversion constructor.
  Arb::Arb (std::string const& number) {
    
    // Call common init.
    _init();
    
    // Set the number.
    set(number);
    
  }
  
  // Accessors.
  Arb& Arb::Base (BaseT const base) {
    if (base != _data->base) {
      _data = new _Data(*_data);
      _data->base = base;
      if (_data->fix) {
        _data->fixq = _DigsT(_data->base).pow(_data->pointpos);
        _reduce();
      }
    }
    return *this;
  }
  Arb& Arb::PointPos (PointPosT const pointpos) {
    if (pointpos != _data->pointpos) {
      _data = new _Data(*_data);
      _data->pointpos = pointpos;
      if (_data->fix) {
        _data->fixq = _DigsT(_data->base).pow(_data->pointpos);
        _reduce();
      }
    }
    return *this;
  }
  Arb& Arb::Fixed (bool const fixed) {
    if (fixed != _data->fix) {
      _data = new _Data(*_data);
      _data->fix = fixed;
      if (_data->fix) {
        _data->fixq = _DigsT(_data->base).pow(_data->pointpos);
      }
      _reduce();
    }
    return *this;
  }
  
  // Reset to just-constructed state.
  Arb& Arb::clear () {
    
    // Clear this number's data. Instead of calling the clear() method of
    // _Data, we are simply creating a new structure and letting the
    // ReferencePointer take care of cleaning up any no-longer referenced
    // data. This is to allow COW.
    _data = new _Data;
    
    // These instructions cannot throw, so they come last.
    _maxradix = 10;
    _format   = FMT_RADIX;
    _propcopy = true;
    _round    = ROUND_NORMAL;
    
    // We done.
    return *this;
    
  }
  
  // Copy another number.
  Arb& Arb::copy (Arb const& number, bool const copynow) {
    
    // Set the new data. Copy if instructed to do so, otherwise just
    // make a reference and wait for COW.
    _DataPT new_data;
    if (copynow) {
      new_data = new _Data(*(number._data));
    } else {
      new_data = number._data;
    }
    
    // Now do non-throwing operations.
    _maxradix = number._maxradix;
    _format   = number._format;
    _propcopy = number._propcopy;
    _round    = number._round;
    _data     = new_data;
    
    // We done.
    return *this;
    
  }
  
  // Convert this number to a string.
  string Arb::toString (OutputFormat const format) const {
    
    // This is the string we will be returning.
    string retval;
    
    // Determine the output format.
    OutputFormat fmt = (format == FMT_DEFAULT) ? _format : format;
    
    // Choose the output format.
    switch (fmt) {
      
      // Output both notations.
      case FMT_BOTH: {
        
        retval += toString(FMT_RADIX) + " " + toString(FMT_FRACTION);
        
      } break;
      
      // Output in radix notation.
      case FMT_DEFAULT:
      case FMT_RADIX: {
        
        // Work area.
        _DigsT numeric;
        numeric.Base(_data->base);
        
        // Get the whole number part.
        numeric = _data->p / _data->q;
        
        // This is the number of digits from the end of the string to put
        // the radix point.
        std::string::size_type radixpos = 0;
        
        // Create the radix part.
        _DigsT remainder = _data->p % _data->q;
        if (((_data->fixq != 0) && (_data->pointpos > 0)) || ((_data->fixq == 0) && (remainder != 0))) {
          
          // Get the radix digits, one by one. Output digits until the entire
          // fraction is output or the maximum requested significant radix digits
          // are output.
          std::string::size_type sigdigs  = 0;
          bool                   sigstart = (numeric != 0);
          _DigsT                 digit;
          digit.Base(_data->base);
          while ((sigdigs < _maxradix) && (remainder != 0)) {
            remainder *= _data->base;
            digit      = remainder / _data->q;
            numeric.push_back(digit);
            ++radixpos;
            remainder %= _data->q;
            if (sigstart || (digit != 0)) {
              ++sigdigs;
              sigstart = true;
            }
          }
          
          // Round.
          if (remainder != 0) {
            switch (_round) {
              case ROUND_UP: {
                if (_data->positive) {
                  ++numeric;
                }
              } break;
              case ROUND_DOWN: {
                if (!_data->positive) {
                  ++numeric;
                }
              } break;
              case ROUND_TOWARD_ZERO: {
              } break;
              case ROUND_FROM_ZERO: {
                ++numeric;
              } break;
              case ROUND_DEFAULT:
              case ROUND_NORMAL: {
                if (remainder * 2 >= _data->q) {
                  ++numeric;
                }
              } break;
            }
          }
          
          // If this is a fixed-radix number, fix the radix.
          if (_data->fix) {
          
            // Pad with zeros.
            if (radixpos < _data->pointpos) {
              numeric  *= _DigsT(_data->base).pow(_data->pointpos - radixpos);
              radixpos  = _data->pointpos;
            }
            
          }
          
        }
        
        // Convert the number to a string.
        retval += numeric.toString();
        
        // Add placeholder zeros.
        if (radixpos >= retval.length()) {
          retval.insert(0, radixpos - retval.length() + 1, '0');
        }
        
        // Place the radix point.
        if (radixpos) {
          retval.insert(retval.length() - radixpos, 1, '.');
        }
        
        // If this is not a fixed-radix number, we may need to remove the radix
        // point.
        if (!_data->fix && radixpos > 0) {
          
          // Strip insignificant zeros.
          if (retval.find_last_not_of('0') != string::npos) {
            retval.erase(retval.find_last_not_of('0') + 1);
          }
          
          // Remove the radix point if it is dangling.
          if ((retval.size() - 1) == retval.find('.')) {
            retval.erase(retval.find('.'));
          }
          
        }
        
      } break;
      
      // Output in fractional format.
      case FMT_FRACTION: {
        
        // Easy, output p/q.
        retval += _data->p.Base(_data->base).toString() + "/" + _data->q.Base(_data->base).toString();
        
      } break;
      
    }
        
    // Output the sign if negative, unless outputting both formats.
    if ((fmt != FMT_BOTH) && !(_data->positive) && (_data->p != 0)) {
      retval.insert(0, 1, '-');
    }
    
    // We done.
    return retval;
    
  }
  
  // Set the number from a string.
  Arb& Arb::set (string const& number) {
    
    // Load the number into this for exception safety.
    Arb new_num;
    
    // Hold the number in case an error needs to be throw.
    ConstReferencePointer<string> tmp_number(new std::string(number));
    
    // Parser will load data into here.
    string            num;
    string            rad;
    string            exp;
    bool              p_num = true;
    bool              p_exp = true;
    string::size_type nexp  = 0;
    
    // Parse the number, scoped for temp variables.
    {
      
      // Data for initial pass.
      enum Mode { NUM, RAD, EXP } mode = NUM;
      string::size_type length   = number.length();
      bool              s_num    = false;
      bool              s_exp    = false;
      bool              diggiven = false;
      
      for (string::size_type i = 0; i != length; ++i) {
        
        switch (number[i]) {
          
          // Decimal point.
          case '.':
            switch (mode) {
              case NUM: mode = RAD;                                                                                                 break;
              case RAD: throw ArbErrors::BadFormat().Problem("Radix point given for a second time").Position(i).Number(tmp_number); break;
              case EXP: throw ArbErrors::BadFormat().Problem("Radix point given in exponent").Position(i).Number(tmp_number);       break;
            }
          break;
          
          // Exponent symbol.
          case 'e':
          case 'E':
            switch (mode) {
              case NUM: mode = EXP;                                                                                                     break;
              case RAD: mode = EXP;                                                                                                     break;
              case EXP: throw ArbErrors::BadFormat().Problem("Exponent symbol given for a second time").Position(i).Number(tmp_number); break;
            }
            diggiven = false;
          break;
          
          // Sign symbol.
          case '+':
          case '-':
            if (diggiven) {
              throw ArbErrors::BadFormat().Problem("Sign given after digits").Position(i).Number(tmp_number);
            }
            switch (mode) {
              case NUM:
                if (s_num) {
                  throw ArbErrors::BadFormat().Problem("Sign of number given for a second time").Position(i).Number(tmp_number);
                }
                p_num = (number[i] == '+');
                s_num = true;
              break;
              case RAD:
                throw ArbErrors::BadFormat().Problem("Sign given after radix point").Position(i).Number(tmp_number);
              break;
              case EXP:
                if (s_exp) {
                  throw ArbErrors::BadFormat().Problem("Sign of exponent given for a second time").Position(i).Number(tmp_number);
                }
                p_exp = (number[i] == '+');
                s_exp = true;
              break;
            }
          break;
          
          // All other characters, most likely digits.
          default:
            
            // Add the digit to its proper place.
            switch (mode) {
              case NUM: num += number[i]; break;
              case RAD: rad += number[i]; break;
              case EXP: exp += number[i]; break;
            }
            diggiven = true;
            
          break;
          
        }
        
      }
      
    }
    
    // Trim insignificant zeros from gathered digits.
    num.erase(0, num.find_first_not_of('0'));
    if (rad.find_last_not_of('0') != string::npos) {
      rad.erase(rad.find_last_not_of('0') + 1);
    }
    exp.erase(0, exp.find_first_not_of('0'));
    
    // Count the number of decimal positions.
    nexp = rad.size();
    
    // Concatenate numeric and radix digits.
    num += rad;
    
    // Load the number.
    new_num._data->p.Base(_data->base) = num;
    
    // Adjust the number based on the exponent. Negative exponent increases
    // radix digits, positive exponent ups order of magnitude.
    {
      
      // Carry fixed-point status from last number.
      new_num._data->pointpos = _data->pointpos;
      new_num._data->fix      = _data->fix;
      
      // Determine the exponent given.
      _DigsT expn(exp);
      _DigsT expr(nexp);
      if (p_exp) {
        if (expn >= expr) {
          expn -= expr;
        } else {
          p_exp = false;
          expn  = expr - expn;
        }
      } else {
        expn += expr;
      }
      
      // Convert to a fully-represented number (no positive exponent).
      if (!expn.isZero()) {
        
        // This calculation will be needed whether exponent is positive or
        // negative. If positive, multiply p by it and clear, thus bringing p
        // down to 1s. If negative, leave as it is, it is already accurate.
        new_num._data->q = _DigsT(_data->base).pow(expn);
        if (p_exp) {
          new_num._data->p *= new_num._data->q;
          new_num._data->q  = 1;
          expn              = 0;
        } 
      }
      
      // If a fixed-point number is requested, increase or decrease the
      // radix digits as needed.
      if (new_num._data->fix) {
        
        // If the exponent is positive, it is a simple case of increasing the
        // number of radix digits, this is a number represented by 1s by now.
        if (p_exp) {
          new_num._data->q  = _DigsT(_data->base).pow(_DigsT(new_num._data->pointpos));
          new_num._data->p *= new_num._data->q;
        
        // If the exponent is negative, we must add or subtract the difference
        // in digits.
        } else {
          if (_DigsT(new_num._data->pointpos) >= expn) {
            _DigsT mod        = _DigsT(_data->base).pow(_DigsT(new_num._data->pointpos) - expn);
            new_num._data->p *= mod;
            new_num._data->q *= mod;
          } else {
            _DigsT mod        = _DigsT(_data->base).pow(expn - _DigsT(new_num._data->pointpos));
            new_num._data->p /= mod;
            new_num._data->q /= mod;
          }
        }
        
        // This is the q that we always need to fix at.
        new_num._data->fixq = new_num._data->q;
        
      }
      
    }
    
    // Set the sign.
    new_num._data->positive = p_num;
    
    // Carry over the old base.
    new_num._data->base = _data->base;
    
    // Reduce the number.
    new_num._reduce();
    
    // The number has been loaded, swap it in. COW is preserved.
    _data = new_num._data;
    return *this;
    
  }
  
  // Set the number from another Arb.
  Arb& Arb::set (Arb const& number) {
    
    // Work area.
    Arb retval(*this, true);
    
    // Set the new number.
    retval._data->p        = number._data->p;
    retval._data->q        = number._data->q;
    retval._data->positive = number._data->positive;
    
    // Reduce the fraction.
    retval._reduce();
    
    // Move the result into place and return.
    _data = retval._data;
    return *this;
    
  }
  
  // Multiplication operator backend.
  Arb& Arb::op_mul (Arb const& number) {
    
    // Work area.
    Arb retval(*this, true);
    
    // Multiply the numbers.
    retval._data->p *= number._data->p;
    retval._data->q *= number._data->q;
    
    // Set the sign.
    retval._data->positive = (retval._data->positive == number._data->positive);
    
    // Reduce the fraction.
    retval._reduce();
    
    // Move the result into place and return.
    _data = retval._data;
    return *this;
    
  }
  
  // Division operator backend.
  Arb& Arb::op_div (Arb const& number) {
    
    // Throw an error on divide by zero.
    if (number == 0) {
      throw ArbErrors::DivByZero();
    }
    
    // Work area
    Arb retval(*this, true);
    
    // Divide the numbers, multiply by the inverse.
    retval._data->p *= number._data->q;
    retval._data->q *= number._data->p;
    
    // Set the sign.
    retval._data->positive = (retval._data->positive == number._data->positive);
    
    // Reduce the fraction.
    retval._reduce();
    
    // Move the result into place and return.
    _data = retval._data;
    return *this;
    
  }
  
  // Modulo division operator backend.
  Arb& Arb::op_mod (Arb const& number) {
    
    // Throw an error on divide by zero.
    if (number == 0) {
      throw ArbErrors::DivByZero();
    }
    
    // Throw an error if both numbers are not integer.
    if (!isInteger() || !number.isInteger()) {
      throw ArbErrors::NonInteger();
    }
    
    // Work area.
    Arb retval(*this, true);
    
    // Simple, just modulo divide p's.
    retval._data->p %= number._data->p;
    
    // We done, return.
    _data = retval._data;
    return *this;
    
  }
  
  // Addition operator backend.
  Arb& Arb::op_add (Arb const& number) {
    
    // If signs are opposite, subtract the negative.
    if (_data->positive != number._data->positive) {
      return op_sub(-number);
    }
    
    // Work area.
    Arb tmp_l(*this,  true);
    Arb tmp_r(number, true);
    
    // Numbers must have the same denominator to add.
    tmp_l._normalize(tmp_r);
    
    // Add the numerators.
    tmp_l._data->p += tmp_r._data->p;
    
    // Reduce the fraction.
    tmp_l._reduce();
    
    // We done. Move the result into place and return.
    _data = tmp_l._data;
    return *this;
    
  }
  
  // Subtraction operator backend.
  Arb& Arb::op_sub (Arb const& number) {
    
    // If signs are opposite, add the negative.
    if (_data->positive != number._data->positive) {
      return op_add(-number);
    }
    
    // Work area.
    Arb tmp_l(*this,  true);
    Arb tmp_r(number, true);
    
    // Numbers must have the same denominator to subtract.
    tmp_l._normalize(tmp_r);
    
    // Add or subtract the numbers.
    if (tmp_r._data->p > tmp_l._data->p) {
      tmp_l._data->p        = tmp_r._data->p - tmp_l._data->p;
      tmp_l._data->positive = !tmp_l._data->positive;
    } else {
      tmp_l._data->p -= tmp_r._data->p;
    }
    
    // Reduce the fraction.
    tmp_l._reduce();
    
    // We done. Move the result into place and return.
    _data = tmp_l._data;
    return *this;
    
  }
  
  // Greater-than operator backend.
  bool Arb::op_gt (Arb const& number) const {
    
    // If one or both numbers are zero, compare is easy.
    if (_data->p.isZero()) {
      if (number._data->p.isZero()) {
        return false;
      } else {
        return !number._data->positive;
      }
    } else if (number._data->p.isZero()) {
      return _data->positive;
    }
    
    // Neither number is zero. If signs are different, they are sufficient
    // for this test.
    if (_data->positive && !number._data->positive) {
      return true;
    } else if (!_data->positive && number._data->positive) {
      return false;
    }
    
    // Signs are the same, we will have to compare numbers. Copy numbers since
    // we will be modifying them.
    Arb tmp_l(*this,  true);
    Arb tmp_r(number, true);
    
    // Numbers must have the same denomiator to compare.
    tmp_l._normalize(tmp_r);
    
    // If numbers are negative, comparison is reversed.
    if (_data->positive) {
      return (tmp_l._data->p > tmp_r._data->p);
    } else {
      return (tmp_l._data->p < tmp_r._data->p);
    }
    
  }
  
  // Less-than operator backend.
  bool Arb::op_lt (Arb const& number) const {
    
    // If one or both numbers are zero, compare is easy.
    if (_data->p.isZero()) {
      if (number._data->p.isZero()) {
        return false;
      } else {
        return number._data->positive;
      }
    } else if (number._data->p.isZero()) {
      return !_data->positive;
    }
    
    // Neither number is zero. If signs are different, they are sufficient for
    // this test.
    if (_data->positive && !number._data->positive) {
      return false;
    } else if (!_data->positive && number._data->positive) {
      return true;
    }
    
    // Signs are the same, we will have to compare numbers.
    Arb tmp_l(*this,  true);
    Arb tmp_r(number, true);
    
    // Numbers must have the same denominator to compare.
    tmp_l._normalize(tmp_r);
    
    // If numbers are negative, comparison is reversed.
    if (_data->positive) {
      return (tmp_l._data->p < tmp_r._data->p);
    } else {
      return (tmp_l._data->p > tmp_r._data->p);
    }
    
  }
  
  // Equal-to operator backend.
  bool Arb::op_eq (Arb const& number) const {
    
    // Check for 0.
    if (_data->p.isZero()) {
      return number._data->p.isZero();
    } else if (number._data->p.isZero()) {
      return false;
    }
    
    // Neither number is zero. Check signs.
    if (_data->positive != number._data->positive) {
      return false;
    }
    
    // Check the numbers themselves. No need to normalize, if they're not,
    // they're not equal.
    return ((_data->q == number._data->q) && (_data->p == number._data->p));
    
  }
  
  // Get the floor of this fractional number.
  Arb Arb::floor () const {
    
    // Work area.
    Arb retval(*this, true);
    
    // Only work if we have to.
    if (!isInteger()) {
      
      // Easy, p/q.
      retval._data->p  /= retval._data->q;
      _DigsT remainder  = retval._data->p % retval._data->q;
      retval._data->q   = 1;
      
      // If the number was negative and there was a remainder, we need to
      // subtract 1.
      if (!isPositive() && (remainder != 0)) {
        --(retval._data->p);
      }
      
    }
    
    // We done.
    return retval;
    
  }
  
  // Raise this number to a power.
  Arb Arb::pow (Arb const& exp) const {
    
    // Work area.
    Arb retval(*this, true);
    
    // No work if this is zero or if we are raising to the 1.
    if (!isZero() || (exp == 1)) {
      
      // Only raise if we have to.
      if (exp != 0) {
        
        // Raise this number to an integer power.
        if (exp.isInteger()) {
          
          // No need to raise 1 or to 1.
          if ((retval.abs() != 1) && (exp.abs() != 1)) {
            
            // Raise p & q.
            retval._data->p = retval._data->p.pow(exp._data->p);
            retval._data->q = retval._data->q.pow(exp._data->p);
            
            // Reduce
            retval._reduce();
            
          }
          
          // The number is positive if it began positive or the exponent is even.
          retval._data->positive = retval._data->positive || exp.isEven();
        
        // Raising to a fraction.
        } else {
          
          // x^(y/z): find the raise to the yth power and find the zth root.
          Arb x;
          Arb y;
          Arb z;
          
          // Raise to the yth power.
          y._data->p = exp._data->p;
          x = pow(y);
          
          // Get the zth root.
          z._data->p = exp._data->q;
          retval = x.root(z);
          
        }
        
        // If exp is negative, 1/pow.
        if (!exp.isPositive()) {
          retval = 1 / retval;
        }
        
      // Raising to the 0 power is always 1.
      } else {
        
        retval = 1;
        
      }
      
    }
    
    // Return the result.
    return retval;
    
  }
  
  // Find the nth root of this number.
  Arb Arb::root (Arb const& n) const {
    
    // No divide by zero.
    if (n.isZero()) {
      throw ArbErrors::DivByZero();
    }
    
    // This is a rational number class, not complex.
    if (!isPositive() && n.isEven()) {
      throw ArbErrors::Complex();
    }
    
    // Common work area.
    Arb retval(1);
    
    // Only find integer roots.
    if (n.isInteger()) {
      
      // Work area.
      Arb lastguess;
      Arb accuracy(Arb(_data->base).pow(-Arb(_maxradix)));
      
      // Create an initial guess, will be within at least one ^2, so Newton's
      // algorithm should begin converging by doubling correct # of bits each
      // iteration.
      if (abs() > 1) {
        retval = 2;
        while (retval.pow(n) < *this) {
          retval *= 2;
        }
      }
      
      Arb precision = retval;
      
      // Newton's algorithm. 
      Arb nmo(n - 1);
      do {
        
        // Save the last guess for comparison and make a new one.
        lastguess = retval;
        retval    = (*this / retval.pow(nmo) + nmo * retval) / n;
        
        // Restrict to the specified precision for performance. Since we know
        // that the number of valid bits doubles each time we iterate, this
        // should be possible to do far more intelligently.
        if (retval._data->q > accuracy._data->q) {
          retval._forcereduce(accuracy._data->q);
        }
        
      // Loop until we are within our specified accuracy.
      } while ((retval - lastguess).abs() >= accuracy);
      
      // Always reduce.
      retval._reduce();
      
    // If non-integer, let pow() take care of making it an integer.
    } else {
      
      retval = pow(1 / n);
      
    }
    
    // Return the result.
    return retval;
    
  }
  
  // Common initialization tasks.
  void Arb::_init () {
    
    // Construct this object fully. By definition of the clear() function,
    // the default constructor must do nothing more than call clear().
    clear();
    
  }
  
  // Reduce the number to its most compact representation.
  Arb& Arb::_reduce () {
    
    // Fixed-point numbers are forced to their dividend.
    if (_data->fix) {
      _forcereduce(_data->fixq);
      
    // Floating-point numbers are simply reduced.
    } else {
      reduce(_data->p, _data->q);
    }
    
    // We done.
    return *this;
    
  }
  
  // Reduce the number to a specific q.
  Arb& Arb::_forcereduce (_DigsT const& q) {
    
    // Only work if we have to.
    if (_data->q != q) {
      
      //  p       x
      // --- == ------
      //  q      fixq
      _DigsT remainder = _data->p * q % _data->q;
      _data->p         = _data->p * q / _data->q;
      
      // Round.
      if (remainder != 0) {
        switch (_round) {
          case ROUND_UP: {
            if (_data->positive) {
              ++_data->p;
            }
          } break;
          case ROUND_DOWN: {
            if (!_data->positive) {
              ++_data->p;
            }
          } break;
          case ROUND_TOWARD_ZERO: {
          } break;
          case ROUND_FROM_ZERO: {
            ++_data->p;
          } break;
          case ROUND_DEFAULT:
          case ROUND_NORMAL: {
            if (remainder * _DigsT(2) >= _data->q) {
              ++_data->p;
            }
          } break;
        }
      }
      
      // Finally, set the new q.
      _data->q = q;
      
    }
    
    // We done.
    return *this;
    
  }
  
  // Normalize two numbers.
  Arb& Arb::_normalize (Arb& number) {
    
    // Only work if necessary.
    if (_data->q != number._data->q) {
      
      // Raise each number's q to their LCM, bring p along.
      _DigsT qgcd(gcd(_data->q, number._data->q));
      _DigsT qlcm((_data->q / qgcd) * number._data->q);
      _data->p        *= number._data->q / qgcd;
      number._data->p *= _data->q        / qgcd;
      _data->q         = qlcm;
      number._data->q  = qlcm;
      
    }
    
    // We done, return.
    return *this;
    
  }
  
  /***************************************************************************
   * Class Arb::_Data.
   ***************************************************************************/
  
  // Default constructor.
  Arb::_Data::_Data () {
    
    // Call common init.
    _init();

  }
  
  // Copy constructor.
  Arb::_Data::_Data (_Data const& data) {
    
    // Call common init.
    _init();
    
    // Copy the given data.
    copy(data);
    
  }
  
  // Assignment operator.
  Arb::_Data& Arb::_Data::operator = (_Data const& data) {
    
    // Copy the given data.
    return copy(data);
    
  }
  
  // Reset to just constructed state.
  Arb::_Data& Arb::_Data::clear () {
    
    // These operations may throw, do them first so any error will be thrown
    // before any changes are made.
    _DigsT new_p;
    _DigsT new_q;
    _DigsT new_fixq;
    new_q.set(1);
    
    // These operations will never throw.
    p    = new_p;
    q    = new_q;
    fixq = new_fixq;
    
    positive = true;
    pointpos = 0;
    fix      = false;
    base     = 10;
    
    // We done.
    return *this;
    
  }
  
  // Copy a given _Data object.
  Arb::_Data& Arb::_Data::copy (_Data const& data) {
    
    // Copy the given data.
    p    = data.p;
    q    = data.q;
    fixq = data.fixq;
    
    positive = data.positive;
    pointpos = data.pointpos;
    fix      = data.fix;
    base     = data.base;
    
    // We done.
    return *this;
    
  }
  
  // Common initialization tasks.
  void Arb::_Data::_init () {
    
    // Construct this object fully. By definition of the clear() function, the
    // default constructor must do nothing more than call clear().
    clear();

  }
  
}