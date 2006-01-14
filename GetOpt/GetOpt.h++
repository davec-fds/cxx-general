/*****************************************************************************
 * GetOpt
 *****************************************************************************
 * This is a C++ wrapper class around getopt and getoptlong.
 * 
 * The interface with getopt is just one nasty hack after another, primarily
 * in error conditions. Since I want to pick up any quirks of getopt, we're
 * pretty much stuck with the nasty hacks. I believe I've caught at least 98%
 * of the error conditions and will report them correctly.
 *****************************************************************************/

// Include guard.
#if !defined(GETOPT_u3p2dg82u3pd8u28u278b)
  #define GETOPT_u3p2dg82u3pd8u28u278b

// Standard includes.
  #include <cctype>

// STL includes.
  #include <string>
  #include <vector>
  #include <algorithm>

// System includes.
  #include <cxx-general/Exception.h++>
  #include <cxx-general/ReferencePointer.h++>
  #include <cxx-general/toString.h++>
  #include <cxx-general/wrapText/wrapText.h++>
  #include <cxx-general/Arb/Arb.h++>
  #include <cxx-general/demangle.h++>

// Namespace wrapping.
namespace DAC {
  
  /***************************************************************************
   * GetOpt
   ***************************************************************************
   * This is the class.
   ***************************************************************************/
  class GetOpt {
    
    /*
     * Private members.
     */
    private:
      
      /***********************************************************************/
      // Forward declarations.
      
      // Internal option representation.
      class _Option;
    
    /*
     * Public members.
     */
    public:
      
      /***********************************************************************/
      // Forward declarations.
      
      // Option readers.
      class ShortOptReader;
      class LongOptReader ;
      
      /***********************************************************************/
      // Errors.
      class Errors {
        
        public:
          
          // All GetOpt errors are based on this.
          class Base : public Exception {
            public:
              virtual ~Base () throw() {};
              virtual char const* what () const throw() { return "Undefined error in GetOpt."; };
          };
          
          // Undefined option was referenced.
          class UndefinedOpt : public Base {
            public:
              virtual ~UndefinedOpt () throw() {};
              virtual char const* what () const throw() { return "Undefined option was referenced."; };
          };
          class UndefinedShort : public UndefinedOpt {
            public:
              virtual ~UndefinedShort () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Undefined short option \"" + DAC::toStringChr(_option) + "\" was referenced.").c_str();
                } catch (...) {
                  return "Undefined short option was referenced. Error creating message string.";
                }
              };
              UndefinedShort& Option (char const option) throw() { _option = option; return *this; };
              char const Option () const throw() { return _option; };
            private:
              char _option;
          };
          class UndefinedLong : public UndefinedOpt {
            public:
              virtual ~UndefinedLong () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Undefined long option \"" + _option + "\" was referenced.").c_str();
                } catch (...) {
                  return "Undefined long option was referenced. Error creating message string.";
                }
              };
              UndefinedLong& Option (std::string const& option) throw() { _option = option; return *this; };
              std::string Option () const throw() { return _option; };
            private:
              std::string _option;
          };
          
          // Attempt to add a duplicate option.
          class DuplicateOption : public Base {
            public:
              virtual ~DuplicateOption () throw() {};
              virtual char const* what () const throw() { return "Attempted to add a duplicate option."; }
          };
          class DuplicateShortOption : public DuplicateOption {
            public:
              virtual ~DuplicateShortOption () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Attempted to add a duplicate short option, \"" + DAC::toStringChr(_option) + "\".").c_str();
                } catch (...) {
                  return "Attempted to add a duplicate short option. Error creating message string.";
                }
              };
              DuplicateShortOption& Option (char const option) throw() { _option = option; return *this; };
              char const Option () const throw() { return _option; };
            private:
              char _option;
          };
          class DuplicateLongOption : public DuplicateOption {
            public:
              virtual ~DuplicateLongOption () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Attempted to add a duplicate long option, \"" + _option + "\".").c_str();
                } catch (...) {
                  return "Attempted to add a duplicate long option. Error creating message string.";
                }
              };
              DuplicateLongOption& Option (std::string const& option) throw() { _option = option; return *this; };
              std::string Option () const throw() { return _option; };
            private:
              std::string _option;
          };
          
          // User error.
          class UserError : public Base {
            public:
              virtual ~UserError () throw() {};
              virtual char const* what () const throw() { return "Unspecified user error in option processing."; };
          };
          
          // User specified an invalid option.
          class InvalidOption : public UserError {
            public:
              virtual ~InvalidOption () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Invalid option passed: " + _option + ".").c_str();
                } catch (...) {
                  return "Invalid option passed. Error creating message string.";
                }
              };
              InvalidOption& Option (std::string const& option) throw () { _option = option; return *this; };
              std::string Option () const throw() { return _option; };
            private:
              std::string _option;
          };
          
          // Option missing a required argument.
          class MissingArg : public UserError {
            public:
              virtual ~MissingArg () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Option " + _option + " is missing a required argument.").c_str();
                } catch (...) {
                  return "Option is missing a required argument. Error creating message string.";
                }
              };
              MissingArg& Option (std::string const& option) throw() { _option = option; return *this; };
              std::string Option () const throw() { return _option; };
            private:
              std::string _option;
          };
          
          // Error converting number.
          class BadNum : public UserError {
            public:
              virtual ~BadNum () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Could not convert option to \"" + _type + "\", lower-level error message is: \"" + _errtext + "\".").c_str();
                } catch (...) {
                  return "Could not convert option to requested type. Error creating message string.";
                }
              };
              BadNum& Type    (std::string const& totype ) throw() { _type    = totype ; return *this; };
              BadNum& ErrText (std::string const& errtext) throw() { _errtext = errtext; return *this; };
              std::string Type    () const throw() { return _type   ; };
              std::string ErrText () const throw() { return _errtext; };
            private:
              std::string _type   ;
              std::string _errtext;
          };
          
          // Unmatched escape character.
          class UnmatchedEscape : public Base {
            public:
              virtual ~UnmatchedEscape () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Unmatched escape character at position " + DAC::toString(_pos) + " in string \"" + _text + "\".").c_str();
                } catch (...) {
                  return "Unmatched escape character in string. Error creating message string.";
                }
              };
              UnmatchedEscape& Position (std::string::size_type const  pos ) { _pos  = pos ; return *this; };
              UnmatchedEscape& Text     (std::string            const& text) { _text = text; return *this; };
              std::string::size_type Position () const { return _pos ; };
              std::string            Text     () const { return _text; };
            private:
              std::string::size_type _pos ;
              std::string            _text;
          };
          
          // Unknown escape character.
          class UnknownEscape : public Base {
            public:
              virtual ~UnknownEscape () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Unknown escape character at position " + DAC::toString(_pos) + " in string \"" + _text + "\".").c_str();
                } catch (...) {
                  return "Unknown escape character in string. Error creating message string.";
                }
              };
              UnknownEscape& Position (std::string::size_type const  pos ) { _pos  = pos ; return *this; };
              UnknownEscape& Text     (std::string            const& text) { _text = text; return *this; };
              std::string::size_type Position () const { return _pos ; };
              std::string            Text     () const { return _text; };
            private:
              std::string::size_type _pos ;
              std::string            _text;
          };
          
          class ArgOOB : public Base {
            public:
              virtual ~ArgOOB () throw () {};
              virtual char const* what () const throw() {
                try {
                  return ("Requested argument number " + DAC::toString(_argnum) + " exceeds argument list of " + DAC::toString(_size) + " arguments.").c_str();
                } catch (...) {
                  return "Requested argument number exceeds argument list size. Error creating message string.";
                }
              };
              virtual ArgOOB& ArgNum (size_t const argnum) { _argnum = argnum; return *this; };
              virtual ArgOOB& Size   (size_t const size  ) { _size   = size  ; return *this; };
              virtual size_t ArgNum () const { return _argnum; };
              virtual size_t Size   () const { return _size  ; };
            private:
              size_t _argnum;
              size_t _size  ;
          };
          class ArgOOBCmdLine : public ArgOOB {
            
          };
          class ArgOOBShort : public ArgOOB {
            public:
              virtual ~ArgOOBShort () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Requested argument number " + DAC::toString(ArgNum()) + " exceeds -" + DAC::toStringChr(_sopt) + " argument list of " + DAC::toString(Size()) + " arguments.").c_str();
                } catch (...) {
                  return "Requested short option argument number exceeds argument list size. Error creating message string.";
                }
              };
              virtual ArgOOBShort& ArgNum (size_t const argnum) { return reinterpret_cast<ArgOOBShort&>(ArgOOB::ArgNum(argnum)); };
              virtual ArgOOBShort& Size   (size_t const size  ) { return reinterpret_cast<ArgOOBShort&>(ArgOOB::Size  (size  )); };
                      ArgOOBShort& Option (char   const sopt  ) { _sopt = sopt; return *this;                                    };
              virtual size_t ArgNum () const { return ArgOOB::ArgNum(); };
              virtual size_t Size   () const { return ArgOOB::Size  (); };
                      char   Option () const { return _sopt           ; };
            private:
              char _sopt;
          };
          class ArgOOBLong : public ArgOOB {
            public:
              virtual ~ArgOOBLong () throw() {};
              virtual char const* what () const throw() {
                try {
                  return ("Requested argument number " + DAC::toString(ArgNum()) + " exceeds --" + _lopt + " argument list of " + DAC::toString(Size()) + " arguments.").c_str();
                } catch (...) {
                  return "Requested long option argument number exceeds argument list size. Error creating message string.";
                }
              };
              virtual ArgOOBLong& ArgNum (size_t      const  argnum) { return reinterpret_cast<ArgOOBLong&>(ArgOOB::ArgNum(argnum)); };
              virtual ArgOOBLong& Size   (size_t      const  size  ) { return reinterpret_cast<ArgOOBLong&>(ArgOOB::Size  (size  )); };
                      ArgOOBLong& Option (std::string const& lopt  ) { _lopt = lopt; return *this;                                   };
              virtual size_t      ArgNum () const { return ArgOOB::ArgNum(); };
              virtual size_t      Size   () const { return ArgOOB::Size  (); };
                      std::string Option () const { return _lopt           ; };
            private:
              std::string _lopt;
          };
        
        // No instances of this class allowed.
        private:
          Errors ();
          Errors (Errors const&);
          Errors& operator = (Errors const&);
        
      };
      
      /***********************************************************************/
      // Data types.
      
      // Whether an option argument is required.
      enum ArgReq { ARG_NONE, ARG_OPTIONAL, ARG_REQUIRED };
      
      // Argument list.
      typedef std::vector<std::string> ArgListT;
      
      // Pointer to argument list.
      typedef ReferencePointer<ArgListT> ArgListPT;
      
      /***********************************************************************
       * Option
       ***********************************************************************
       * Describes an option.
       ***********************************************************************/
      class Option {
        
        /*
         * Public members.
         */
        public:
          
          /*******************************************************************/
          // Friends.
          
          // Option readers.
          friend class ShortOptReader;
          friend class LongOptReader ;
          
          /*******************************************************************/
          // Function members.
          
          // Constructor.
          Option (char const sopt, std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname);
          Option (char const sopt,                          ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname);
          Option (                 std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname);
          
          // Properties.
          Option& Short          (char        const  sopt   );
          Option& Long           (std::string const& lopt   );
          Option& ArgRequirement (ArgReq      const  argreq );
          Option& Required       (bool        const  optreq );
          Option& Help           (std::string const& help   );
          Option& ArgName        (std::string const& argname);
          char        Short          () const;
          std::string Long           () const;
          ArgReq      ArgRequirement () const;
          bool        Required       () const;
          std::string Help           () const;
          std::string ArgName        () const;
          
          // Info.
          bool isShort () const;
          bool isLong  () const;
          
        /*
         * Private members.
         */
        private:
          
          /*******************************************************************/
          // Data members.
          
          char        _sopt      ;
          std::string _lopt      ;
          ArgReq      _argreq    ;
          bool        _optreq    ;
          std::string _help      ;
          std::string _argname   ;
          bool        _isset_sopt;
          bool        _isset_lopt;
          
      };
      
      /***********************************************************************
       * ArgReader
       ***********************************************************************
       * Reads an argument. Mostly used for operator access.
       ***********************************************************************/
      class ArgReader {
        
        /*
         * Public members.
         */
        public:
          
          /*******************************************************************/
          // Function members.
          
          // Constructor.
          ArgReader (std::string const& arg);
          
          // Conversion operator.
          template <class T> operator T () const;
          
        /*
         * Private members.
         */
        private:
          
          /*******************************************************************/
          // Data members.
          
          // The argument.
          std::string const& _arg;
        
      };
      
      /***********************************************************************
       * ShortOptReader
       ***********************************************************************
       * Reads a short option. Mostly used for operator access.
       ***********************************************************************/
      class ShortOptReader {
        
        /*
         * Public members.
         */
        public:
          
          /*******************************************************************/
          // Function members.
          
          // Constructor.
          ShortOptReader (_Option const& opt);
          
          // Conversion operator. Returns whether this option is set.
          operator bool () const;
          
          // Element access operator, read option argument.
          ArgReader operator [] (size_t const argnum) const;
          
        /*
         * Private members.
         */
        private:
          
          /*******************************************************************/
          // Data members.
          
          // The option.
          _Option const& _opt;
        
      };
      
      /***********************************************************************
       * LongOptReader
       ***********************************************************************
       * Reads a long option. Mostly used for operator access.
       ***********************************************************************/
      class LongOptReader {
        
        /*
         * Public members.
         */
        public:
          
          /*******************************************************************/
          // Function members.
          
          // Constructor.
          LongOptReader (_Option const& opt);
          
          // Conversion operator. Returns whether this option is set.
          operator bool () const;
          
          // Element access operator, read option argument.
          ArgReader operator [] (size_t const argnum) const;
          
        /*
         * Private members.
         */
        private:
          
          /*******************************************************************/
          // Data members.

          // The option.
          _Option const& _opt;
          
      };
      
      // List of options.
      typedef std::vector<Option> Options;
      
      /***********************************************************************/
      // Function members.
      
      // Default constructor.
      GetOpt ();
      
      // Copy constructor.
      GetOpt (GetOpt const& source, bool const deep = false);
      
      // argc & argv constructor.
      GetOpt (int const argc, char const* const* const argv);
      
      // Valid options constructor.
      GetOpt (Options const& options);
      
      // Element access operator, read command line argument.
      ArgReader operator [] (size_t const element) const;
      
      // Element access operator, read option.
      ShortOptReader operator [] (char        const  sopt) const;
      LongOptReader  operator [] (std::string const& lopt) const;
      
      // Assignment operator.
      GetOpt& operator = (GetOpt const& right) throw();
      
      // Properties.
      GetOpt& CheckLong   (bool        const  checklong  );
      GetOpt& CheckShort  (bool        const  checkshort );
      GetOpt& POSIXCheck  (bool        const  posixcheck );
      GetOpt& ProgramName (std::string const& programname);
      GetOpt& Usage       (std::string const& usage      );
      GetOpt& Description (std::string const& description);
      GetOpt& PostInfo    (std::string const& postinfo   );
      GetOpt& BugAddress  (std::string const& bugaddress );
      GetOpt& HelpWidth   (size_t      const  helpwidth  );
      bool        CheckLong   () const;
      bool        CheckShort  () const;
      bool        POSIXCheck  () const;
      std::string ProgramName () const;
      std::string Usage       () const;
      std::string Description () const;
      std::string PostInfo    () const;
      std::string BugAddress  () const;
      size_t      HelpWidth   () const;
      
      // Reset to just-constructed state.
      void clear ();
      
      // Copy a given GetOpt.
      void copy (GetOpt const& source, bool const deep = false) throw();
      
      // See if a particular option has been defined.
      bool isDefined (char        const  sopt) const;
      bool isDefined (std::string const& lopt) const;
      
      // See if a particular option is set.
      bool isSet (char        const  sopt) const;
      bool isSet (std::string const& lopt) const;
      
      // See how many times an option has been set.
      size_t numSet (char        const  sopt) const;
      size_t numSet (std::string const& lopt) const;
      
      // See how many arguments we have. First form is for non-option args.
      size_t numArgs (                       ) const;
      size_t numArgs (char        const  sopt) const;
      size_t numArgs (std::string const& lopt) const;
      
      // Get arguments. First form is for non-option args.
      template <class T> T getArg (                         size_t const argnum) const;
      template <class T> T getArg (char const sopt        , size_t const argnum) const;
      template <class T> T getArg (std::string const& lopt, size_t const argnum) const;
      
      // Get all arguments as a list.
      template <class T> ReferencePointer< std::vector<T> > getArgs (                       ) const;
      template <class T> ReferencePointer< std::vector<T> > getArgs (char        const  sopt) const;
      template <class T> ReferencePointer< std::vector<T> > getArgs (std::string const& lopt) const;
      
      // Get command-line arguments in order.
      ArgListPT getOrdered () const;
      
      // Set the command-line arguments.
      GetOpt& set_cmdArgs (int const argc, char const* const* const argv);
      
      // Set the valid options. This will overwrite any previous options.
      GetOpt& set_options (Options const& options);
      
      // Add a valid option.
      GetOpt& add_option (Option const& option);
      
      // Get help string.
      std::string getShortHelp () const;
      std::string getHelp      () const;
      
      // Scan the options. You will probably never use this function.
      void scan () const;
    
    /*
     * Private members.
     */
    private:
      
      /***********************************************************************/
      // Data types.
      
      // List of arguments.
      typedef std::vector<std::string> _ArgList;
      
      /***********************************************************************
       * _Option
       ***********************************************************************
       * Internal options structure, with status.
       ***********************************************************************/
      class _Option : public Option {
        
        /*
         * Public members.
         */
        public:
          
          /*******************************************************************/
          // Function members.
          
          // Constructors.
          _Option (char const sopt, std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname);
          _Option (char const sopt,                          ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname);
          _Option (                 std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname);
          _Option (Option const& option);
          
          // Convert argument requirement to glibc's getopt arg requirement.
          int to_getoptArgReq () const;
          
          /*******************************************************************/
          // Data members.
          
          // Number of times this option has been set.
          size_t numset;
          
          // Arguments to this option.
          _ArgList args;
          
      };
      
      // List of internal options.
      typedef std::vector<_Option> _Options;
      
      /***********************************************************************
       * _Data
       ***********************************************************************
       * This is the data store type, wrapped in one class for easy COW.
       ***********************************************************************/
      class _Data {
        
        /*
         * Public members.
         */
        public:
          
          /*******************************************************************/
          // Data members.
          
          // Command-line arguments.
          _ArgList argv;
          
          // Option info.
          _Options options;
          
          // Non-option command-line arguments.
          _ArgList arguments;
          
          // Command-line arguments in order.
          _ArgList ordered;
          
          // True if data has been modified in a way that requires re-process
          // of arguments.
          bool modified;
          
          // Number of long and short arguments.
          size_t numlong ;
          size_t numshort;
          
          // Check long and short options.
          bool checklong ;
          bool checkshort;
          
          // Strict POSIX checking.
          bool posixcheck;
          
          // Help info.
          std::string programname;
          std::string usage      ;
          std::string description;
          std::string postinfo   ;
          std::string bugaddress ;
          size_t      helpwidth  ;
          
          /*******************************************************************/
          // Function members.
          
          // Default constructor.
          _Data ();
          
          // Copy constructor.
          _Data (_Data const& source);
          
          // Assignment operator.
          _Data& operator = (_Data const& right);
          
          // Reset to just-constructed defaults.
          _Data& clear ();
          
          // Copy another _Data object.
          _Data& copy (_Data const& source);
          
      };
      
      // Reference pointer to class data.
      typedef ReferencePointer<_Data> _DataPT;
      
      /***********************************************************************/
      // Data members.
      
      // All data is in here.
      _DataPT _data;
      
      /***********************************************************************/
      // Function members.
      
      // Add a valid option.
      void _add_option (Option const& option);
      
      // Find a given option.
      _Option* _find_option (char        const  sopt) const;
      _Option* _find_option (std::string const& lopt) const;
      
      // Find a partial match for a long option. If a perfect match is found,
      // stop looking. If an ambiguous match is found, return null pointer.
      _Option* _find_part_option (std::string const& lopt) const;
      
      // Find a given option, scan args if needed.
      _Option* _scan_option (char        const  sopt) const;
      _Option* _scan_option (std::string const& lopt) const;
      
      /***********************************************************************/
      // Static function members.
      
      // Process text for soft hyphens (%h), non-breaking characters (%n),
      // zero-width spaces (%z), and replace %s with a second passed string.
      static std::string _procText (std::string const& text, std::string const& replace,
                                    wrapText::POIContainer& shy,
                                    wrapText::POIContainer& nb ,
                                    wrapText::POIContainer& zws );
      
      // Convert a given string to bool.
      static bool _toBool (std::string const& text);
      
      // Convert a string to uppercase.
      static std::string _uppercase (std::string const& text);
      
      // Convert a string to a given type.
      template <class T> static T _convert (std::string const& text);
      
      // Convert a list of arguments to a given type.
      template <class T> static ReferencePointer< std::vector<T> > _convert_ArgList (_ArgList const& args);
      
  };
  
  /***************************************************************************
   * Explicit template instantiations.
   ***************************************************************************/
  
  /***************************************************************************/
  // Function members.

  // Get arguments.
  template <> std::string GetOpt::getArg<std::string> (                         size_t const argnum) const;
  template <> std::string GetOpt::getArg<std::string> (char        const  sopt, size_t const argnum) const;
  template <> std::string GetOpt::getArg<std::string> (std::string const& lopt, size_t const argnum) const;
  
  /***************************************************************************
   * Inline and template definitions.
   ***************************************************************************/
  
  /***************************************************************************
   * GetOpt
   ***************************************************************************/
  
  /***************************************************************************/
  // Function members.
  
  /*
   * Default constructor.
   */
  inline GetOpt::GetOpt () { clear(); }
  
  /*
   * Copy constructor.
   */
  inline GetOpt::GetOpt (GetOpt const& source, bool const deep) { copy(source, deep); }
  
  /*
   * Element access operator, read command line argument.
   */
  inline GetOpt::ArgReader GetOpt::operator [] (size_t const element) const { return getArg<std::string>(element); }
  
  /*
   * Element access operator, read option.
   */
  inline GetOpt::ShortOptReader GetOpt::operator [] (char        const  sopt) const { return *_scan_option(sopt); }
  inline GetOpt::LongOptReader  GetOpt::operator [] (std::string const& lopt) const { return *_scan_option(lopt); }
  
  /*
   * Assignment operator.
   */
  inline GetOpt& GetOpt::operator = (GetOpt const& source) throw () { copy(source); return *this; }
  
  /*
   * Properties.
   */
  inline GetOpt& GetOpt::CheckLong (bool checklong ) {
    if (checklong != _data->checklong ) {
      GetOpt tmp(*this, true);
      tmp._data->modified  = true;
      tmp._data->checklong = checklong;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::CheckShort (bool checkshort) {
    if (checkshort != _data->checkshort) {
      GetOpt tmp(*this, true);
      tmp._data->modified   = true      ;
      tmp._data->checkshort = checkshort;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::POSIXCheck (bool posixcheck) {
    if (posixcheck != _data->posixcheck) {
      GetOpt tmp(*this, true);
      tmp._data->modified   = true      ;
      tmp._data->posixcheck = posixcheck;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::ProgramName (std::string const& programname) {
    if (programname != _data->programname) {
      GetOpt tmp(*this, true);
      tmp._data->programname = programname;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::Usage (std::string const& usage) {
    if (usage != _data->usage) {
      GetOpt tmp(*this, true);
      tmp._data->usage = usage;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::Description (std::string const& description) {
    if (description != _data->description) {
      GetOpt tmp(*this, true);
      tmp._data->description = description;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::PostInfo (std::string const& postinfo) {
    if (postinfo != _data->postinfo) {
      GetOpt tmp(*this, true);
      tmp._data->postinfo = postinfo;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::BugAddress (std::string const& bugaddress) {
    if (bugaddress != _data->bugaddress) {
      GetOpt tmp(*this, true);
      tmp._data->bugaddress = bugaddress;
      _data = tmp._data;
    }
    return *this;
  }
  inline GetOpt& GetOpt::HelpWidth (size_t const helpwidth) {
    if (helpwidth != _data->helpwidth) {
      GetOpt tmp(*this, true);
      tmp._data->helpwidth = helpwidth;
      _data = tmp._data;
    }
    return *this;
  }
  inline bool        GetOpt::CheckLong   () const { return _data->checklong  ; }
  inline bool        GetOpt::CheckShort  () const { return _data->checkshort ; }
  inline bool        GetOpt::POSIXCheck  () const { return _data->posixcheck ; }
  inline std::string GetOpt::ProgramName () const { return _data->programname; }
  inline std::string GetOpt::Usage       () const { return _data->usage      ; }
  inline std::string GetOpt::Description () const { return _data->description; }
  inline std::string GetOpt::PostInfo    () const { return _data->postinfo   ; }
  inline std::string GetOpt::BugAddress  () const { return _data->bugaddress ; }
  inline size_t      GetOpt::HelpWidth   () const { return _data->helpwidth  ; }
  
  /*
   * See if an option has been defined.
   */
  inline bool GetOpt::isDefined (char        const  sopt) const { return _find_option(sopt); }
  inline bool GetOpt::isDefined (std::string const& lopt) const { return _find_option(lopt); }
  
  /*
   * See if an option has been set.
   */
  inline bool GetOpt::isSet (char        const  sopt) const { return numSet(sopt); }
  inline bool GetOpt::isSet (std::string const& lopt) const { return numSet(lopt); }
  
  /*
   * See how many times an option has been set.
   */
  inline size_t GetOpt::numSet (char        const  sopt) const { return _scan_option(sopt)->numset; }
  inline size_t GetOpt::numSet (std::string const& lopt) const { return _scan_option(lopt)->numset; }
  
  /*
   * See how many arguments an option or the command-line has.
   */
  inline size_t GetOpt::numArgs (                       ) const { if (_data->modified) { scan(); } return _data->arguments.size(); }
  inline size_t GetOpt::numArgs (char        const  sopt) const { return _scan_option(sopt)->args.size(); }
  inline size_t GetOpt::numArgs (std::string const& lopt) const { return _scan_option(lopt)->args.size(); }
  
  /*
   * Get arguments. First form is for non-option args.
   */
  template <class T> T GetOpt::getArg (size_t const argnum) const {
    if (_data->modified) {
      scan();
    }
    if (argnum >= _data->arguments.size()) {
      throw Errors::ArgOOBCmdLine().ArgNum(argnum).Size(_data->arguments.size());
    }
    return _convert<T>(_data->arguments[argnum]);
  }
  template <class T> T GetOpt::getArg (char const sopt, size_t const argnum) const {
    _ArgList const& work = _scan_option(sopt)->args;
    if (argnum >= work.size()) {
      throw Errors::ArgOOBShort().ArgNum(argnum).Size(work.size()).Option(sopt);
    }
    return _convert<T>(work[argnum]);
  }
  template <class T> T GetOpt::getArg (std::string const& lopt, size_t const argnum) const {
    _ArgList const& work = _scan_option(lopt)->args;
    if (argnum >= work.size()) {
      throw Errors::ArgOOBLong().ArgNum(argnum).Size(work.size()).Option(lopt);
    }
    return _convert<T>(work[argnum]);
  }
      
  /*
   * Get all arguments as a list.
   */
  
  // std::string.
  template <> inline ReferencePointer< std::vector<std::string> > GetOpt::getArgs<std::string> () const {
    if (_data->modified) {
      scan();
    }
    return ReferencePointer< std::vector<std::string> >(new std::vector<std::string>(_data->arguments));
  }
  template <> inline ReferencePointer< std::vector<std::string> > GetOpt::getArgs<std::string> (char const sopt) const {
    return ReferencePointer< std::vector<std::string> >(new std::vector<std::string>(_scan_option(sopt)->args));
  }
  template <> inline ReferencePointer< std::vector<std::string> > GetOpt::getArgs<std::string> (std::string const& lopt) const {
    return ReferencePointer< std::vector<std::string> >(new std::vector<std::string>(_scan_option(lopt)->args));
  }
  
  // Other.
  template <class T> inline ReferencePointer< std::vector<T> > GetOpt::getArgs () const {
    if (_data->modified) {
      scan();
    }
    return _convert_ArgList<T>(_data->arguments);
  }
  template <class T> inline ReferencePointer< std::vector<T> > GetOpt::getArgs (char const sopt) const {
    return _convert_ArgList<T>(_scan_option(sopt)->args);
  }
  template <class T> inline ReferencePointer< std::vector<T> > GetOpt::getArgs (std::string const& lopt) const {
    return _convert_ArgList<T>(_scan_option(lopt)->args);
  }
  
  /*
   * Get ordered command-line arguments.
   */
  inline GetOpt::ArgListPT GetOpt::getOrdered () const { if (_data->modified) { scan(); } return ArgListPT(new ArgListT(_data->ordered)); }
  
  /*
   * Convert a string to uppercase.
   */
  inline std::string GetOpt::_uppercase (std::string const& text) {
    std::string retval;
    retval.reserve(text.length());
    transform(text.begin(), text.end(), retval.begin(), toupper);
    return retval;
  }
  
  /*
   * Convert a string to a given type.
   */
  // bool.
  template <> inline bool GetOpt::_convert (std::string const& text) { return _toBool(text); }
  
  // Numeric type.
  template <class T> T GetOpt::_convert (std::string const& text) {
    T retval;
    try {
      retval = Arb(text);
    } catch (Arb::Errors::Base& e) {
      throw Errors::BadNum().Type(demangle(retval)).ErrText(e.what());
    }
    return retval;
  }
  
  /*
   * Convert a list of arguments to a given type.
   */
  template <class T> ReferencePointer< std::vector<T> > GetOpt::_convert_ArgList (_ArgList const& args) {
    
    // Work area.
    ReferencePointer< std::vector<T> > retval;
    
    // Attempt to convert to a numeric type.
    for (_ArgList::iterator i = args.begin(); i != args.end(); ++i) {
      retval->push_back(_convert<T>(*i));
    }
    
    // Done.
    return retval;
    
  }
  
  /***************************************************************************
   * GetOpt::ArgReader
   ***************************************************************************/
  
  /***************************************************************************/
  // Function members.
  
  /*
   * Constructor.
   */
  inline GetOpt::ArgReader::ArgReader (std::string const& arg) : _arg(arg) {}
  
  /*
   * Conversion operator.
   */
  template <> inline GetOpt::ArgReader::operator std::string () const { return _arg; }
  template <class T> inline GetOpt::ArgReader::operator T () const { return _convert<T>(_arg); }
  
  /***************************************************************************
   * GetOpt::ShortOptReader
   ***************************************************************************/
  
  /***************************************************************************/
  // Function members.
  
  /*
   * Constructor.
   */
  inline GetOpt::ShortOptReader::ShortOptReader (_Option const& opt) : _opt(opt) {}
  
  /*
   * Conversion operator. Returns whether this option is set.
   */
  inline GetOpt::ShortOptReader::operator bool () const { return _opt.numset; }
  
  /*
   * Element access operator, read option argument.
   */
  inline GetOpt::ArgReader GetOpt::ShortOptReader::operator [] (size_t const argnum) const { 
    if (argnum >= _opt.args.size()) {
      throw Errors::ArgOOBShort().ArgNum(argnum).Size(_opt.args.size()).Option(_opt._sopt);
    }
    return _opt.args[argnum];
  }
  
  /***************************************************************************
   * GetOpt::LongOptReader
   ***************************************************************************/
  
  /***************************************************************************/
  // Function members.

  /*
   * Constructor.
   */
  inline GetOpt::LongOptReader::LongOptReader (_Option const& opt) : _opt(opt) {}
  
  /*
   * Conversion operator. Returns whether this option is set.
   */
  inline GetOpt::LongOptReader::operator bool () const { return _opt.numset; }
  
  /*
   * Element access operator, read option argument.
   */
  inline GetOpt::ArgReader GetOpt::LongOptReader::operator [] (size_t const argnum) const {
    if (argnum >= _opt.args.size()) {
      throw Errors::ArgOOBLong().ArgNum(argnum).Size(_opt.args.size()).Option(_opt._lopt);
    }
    return _opt.args[argnum];
  }
  
  /***************************************************************************
   * GetOpt::_Data
   ***************************************************************************/
  
  /***************************************************************************/
  // Function members.
  
  /*
   * _Data default constructor.
   */
  inline GetOpt::_Data::_Data () { clear(); }
  
  /*
   * _Data copy constructor.
   */
  inline GetOpt::_Data::_Data (_Data const& source) { copy(source); }
  
  /*
   * _Data assignment operator.
   */
  inline GetOpt::_Data& GetOpt::_Data::operator = (_Data const& source) { return copy(source); }
  
  /*
   * Option constructor.
   */
  inline GetOpt::Option::Option (char const sopt, std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname) :
    _sopt(sopt), _lopt(lopt), _argreq(argreq), _optreq(optreq), _help(help), _argname(argname), _isset_sopt(true), _isset_lopt(true)
  {}
  inline GetOpt::Option::Option (char const sopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname) :
    _sopt(sopt), _argreq(argreq), _optreq(optreq), _help(help), _argname(argname), _isset_sopt(true), _isset_lopt(false)
  {}
  inline GetOpt::Option::Option (std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname) :
    _lopt(lopt), _argreq(argreq), _optreq(optreq), _help(help), _argname(argname), _isset_sopt(false), _isset_lopt(true)
  {}
  
  /*
   * _Option constructor.
   */
  inline GetOpt::_Option::_Option (char const sopt, std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname) :
    Option(sopt, lopt, argreq, optreq, help, argname), numset(0)
  {}
  inline GetOpt::_Option::_Option (char const sopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname) :
    Option(sopt, argreq, optreq, help, argname), numset(0)
  {}
  inline GetOpt::_Option::_Option (std::string const& lopt, ArgReq const argreq, bool const optreq, std::string const& help, std::string const& argname) :
    Option(lopt, argreq, optreq, help, argname), numset(0)
  {}
  inline GetOpt::_Option::_Option (Option const& option) :
    Option(option), numset(0)
  {}
  
  /*
   * Option properties.
   */
  inline GetOpt::Option& GetOpt::Option::Short          (char        const  sopt   ) { _sopt    = sopt   ; _isset_sopt = sopt != '\0' ; return *this; }
  inline GetOpt::Option& GetOpt::Option::Long           (std::string const& lopt   ) { _lopt    = lopt   ; _isset_lopt = !lopt.empty(); return *this; }
  inline GetOpt::Option& GetOpt::Option::ArgRequirement (ArgReq      const  argreq ) { _argreq  = argreq ;                              return *this; }
  inline GetOpt::Option& GetOpt::Option::Required       (bool        const  optreq ) { _optreq  = optreq ;                              return *this; }
  inline GetOpt::Option& GetOpt::Option::Help           (std::string const& help   ) { _help    = help   ;                              return *this; }
  inline GetOpt::Option& GetOpt::Option::ArgName        (std::string const& argname) { _argname = argname;                              return *this; }
  inline char           GetOpt::Option::Short          () const { return _sopt      ; }
  inline std::string    GetOpt::Option::Long           () const { return _lopt      ; }
  inline GetOpt::ArgReq GetOpt::Option::ArgRequirement () const { return _argreq    ; }
  inline bool           GetOpt::Option::Required       () const { return _optreq    ; }
  inline std::string    GetOpt::Option::Help           () const { return _help      ; }
  inline std::string    GetOpt::Option::ArgName        () const { return _argname   ; }
  inline bool           GetOpt::Option::isShort        () const { return _isset_sopt; }
  inline bool           GetOpt::Option::isLong         () const { return _isset_lopt; }
}

#endif

