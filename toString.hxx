/*****************************************************************************
 * toString.hxx
 *****************************************************************************
 * Convert a number to a string.
 *****************************************************************************/

// Include guard.
#if !defined(TOSTRING_buhu84hahasetkbx842)
  #define TOSTRING_buhu84hahasetkbx842
  
  // STL includes.
  #include <sstream>
  
  // Contain in namespace.
  namespace DAC {
    
    // Convert the number to a string.
    template <class T> std::string toString (T const& from);
    
    template <> std::string toString<char> (char const& from) {
      std::ostringstream os;
      os << static_cast<int>(from);
      return os.str();
    }
    
    template <> std::string toString<signed char> (signed char const& from) {
      std::ostringstream os;
      os << static_cast<int>(from);
      return os.str();
    }
    
    template <> std::string toString<unsigned char> (unsigned char const& from) {
      std::ostringstream os;
      os << static_cast<unsigned int>(from);
      return os.str();
    }
    
    template <class T> std::string toString (T const& from) {
      std::ostringstream os;
      os << from;
      return os.str();
    }
    
  };
  
#endif