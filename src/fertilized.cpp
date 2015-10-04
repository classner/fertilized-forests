// Ensure that there is always a library file created in Windows.
namespace fertilized {
#if defined(_MSC_VER)
  __declspec( dllexport )
#endif
	int dummyfunc() {
	  return 0;
  };
};
