#include "template-hsc.h"

int main (int argc, char *argv [])
{
#if __GLASGOW_HASKELL__ && __GLASGOW_HASKELL__ < 409
    printf ("{-# OPTIONS -optc-D__GLASGOW_HASKELL__=%d #-}\n", 603);
#endif
    hsc_line (1, "Directory.hsc");
    fputs ("{-# OPTIONS -fffi #-}\n"
           "", stdout);
    hsc_line (2, "Directory.hsc");
    fputs ("-----------------------------------------------------------------------------\n"
           "-- |\n"
           "-- Module      :  System.Posix.Files\n"
           "-- Copyright   :  (c) The University of Glasgow 2002\n"
           "-- License     :  BSD-style (see the file libraries/base/LICENSE)\n"
           "-- \n"
           "-- Maintainer  :  libraries@haskell.org\n"
           "-- Stability   :  provisional\n"
           "-- Portability :  non-portable (requires POSIX)\n"
           "--\n"
           "-- POSIX directory support\n"
           "--\n"
           "-----------------------------------------------------------------------------\n"
           "\n"
           "module System.Posix.Directory (\n"
           "   -- * Creating and removing directories\n"
           "   createDirectory, removeDirectory,\n"
           "\n"
           "   -- * Reading directories\n"
           "   DirStream,\n"
           "   openDirStream,\n"
           "   readDirStream,\n"
           "   rewindDirStream,   \n"
           "   closeDirStream,\n"
           "   DirStreamOffset,\n"
           "   tellDirStream,\n"
           "   seekDirStream,\n"
           "\n"
           "   -- * The working dirctory\n"
           "   getWorkingDirectory,\n"
           "   changeWorkingDirectory,\n"
           "   changeWorkingDirectoryFd,\n"
           "  ) where\n"
           "\n"
           "import System.Posix.Types\n"
           "import System.Posix.Internals\n"
           "import System.Directory hiding (createDirectory)\n"
           "import Foreign\n"
           "import Foreign.C\n"
           "\n"
           "createDirectory :: FilePath -> FileMode -> IO ()\n"
           "createDirectory name mode =\n"
           "  withCString name $ \\s -> \n"
           "    throwErrnoIfMinus1_ \"createDirectory\" (c_mkdir s mode)  \n"
           "\n"
           "foreign import ccall unsafe \"mkdir\"\n"
           "  c_mkdir :: CString -> CMode -> IO CInt\n"
           "\n"
           "newtype DirStream = DirStream (Ptr CDir)\n"
           "\n"
           "openDirStream :: FilePath -> IO DirStream\n"
           "openDirStream name =\n"
           "  withCString name $ \\s -> do\n"
           "    dirp <- throwErrnoIfNull \"openDirStream\" $ c_opendir s\n"
           "    return (DirStream dirp)\n"
           "\n"
           "readDirStream :: DirStream -> IO FilePath\n"
           "readDirStream (DirStream dirp) =\n"
           "  alloca $ \\ptr_dEnt  -> loop ptr_dEnt\n"
           " where\n"
           "  loop ptr_dEnt = do\n"
           "    resetErrno\n"
           "    r <- readdir dirp ptr_dEnt\n"
           "    if (r == 0)\n"
           "\t then do dEnt <- peek ptr_dEnt\n"
           "\t\t if (dEnt == nullPtr)\n"
           "\t\t    then return []\n"
           "\t\t    else do\n"
           "\t \t     entry <- (d_name dEnt >>= peekCString)\n"
           "\t\t     freeDirEnt dEnt\n"
           "\t\t     return entry\n"
           "\t else do errno <- getErrno\n"
           "\t\t if (errno == eINTR) then loop ptr_dEnt else do\n"
           "\t\t let (Errno eo) = errno\n"
           "\t\t if (eo == end_of_dir)\n"
           "\t\t    then return []\n"
           "\t\t    else throwErrno \"readDirStream\"\n"
           "\n"
           "rewindDirStream :: DirStream -> IO ()\n"
           "rewindDirStream (DirStream dirp) = c_rewinddir dirp\n"
           "\n"
           "closeDirStream :: DirStream -> IO ()\n"
           "closeDirStream (DirStream dirp) = do\n"
           "  throwErrnoIfMinus1_ \"closeDirStream\" (c_closedir dirp)\n"
           "\n"
           "newtype DirStreamOffset = DirStreamOffset CLong\n"
           "\n"
           "seekDirStream :: DirStream -> DirStreamOffset -> IO ()\n"
           "seekDirStream (DirStream dirp) (DirStreamOffset off) =\n"
           "  c_seekdir dirp off\n"
           "\n"
           "foreign import ccall unsafe \"seekdir\"\n"
           "  c_seekdir :: Ptr CDir -> CLong -> IO ()\n"
           "\n"
           "tellDirStream :: DirStream -> IO DirStreamOffset\n"
           "tellDirStream (DirStream dirp) = do\n"
           "  off <- c_telldir dirp\n"
           "  return (DirStreamOffset off)\n"
           "\n"
           "foreign import ccall unsafe \"telldir\"\n"
           "  c_telldir :: Ptr CDir -> IO CLong\n"
           "\n"
           "{-\n"
           " Renamings of functionality provided via Directory interface,\n"
           " kept around for b.wards compatibility and for having more POSIXy\n"
           " names\n"
           "-}\n"
           "getWorkingDirectory :: IO FilePath\n"
           "getWorkingDirectory = getCurrentDirectory\n"
           "\n"
           "changeWorkingDirectory :: FilePath -> IO ()\n"
           "changeWorkingDirectory name = setCurrentDirectory name\n"
           "\n"
           "changeWorkingDirectoryFd :: Fd -> IO ()\n"
           "changeWorkingDirectoryFd (Fd fd) = \n"
           "  throwErrnoIfMinus1_ \"changeWorkingDirectoryFd\" (c_fchdir fd)\n"
           "\n"
           "foreign import ccall unsafe \"fchdir\"\n"
           "  c_fchdir :: CInt -> IO CInt\n"
           "", stdout);
    return 0;
}
