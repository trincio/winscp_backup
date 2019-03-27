/*
 * Coroutine mechanics used in PuTTY's SSH code.
 */

#ifndef PUTTY_SSHCR_H
#define PUTTY_SSHCR_H

/*
 * If these macros look impenetrable to you, you might find it helpful
 * to read
 * 
 *   https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
 * 
 * which explains the theory behind these macros.
 * 
 * In particular, if you are getting `case expression not constant'
 * errors when building with MS Visual Studio, this is because MS's
 * Edit and Continue debugging feature causes their compiler to
 * violate ANSI C. To disable Edit and Continue debugging:
 * 
 *  - right-click ssh.c in the FileView
 *  - click Settings
 *  - select the C/C++ tab and the General category
 *  - under `Debug info:', select anything _other_ than `Program
 *    Database for Edit and Continue'.
 */

#define crBegin(v)      { int *crLine = &v; switch(v) { case 0:;
#define crBeginState    crBegin(s->crLine)
#define crStateP(t, v)                          \
    struct t *s;                                \
    if (!(v)) { s = (v) = snew(struct t); s->crLine = 0; }      \
    s = (v);
#define crState(t)      crStateP(t, ssh->t)
#define crFinish(z)     } *crLine = 0; return (z); }
#define crFinishV       } *crLine = 0; return; }
#define crFinishFree(z) } sfree(s); return (z); }
#define crFinishFreeV   } sfree(s); return; }
#define crReturn(z)     \
        do {\
            *crLine =__LINE__; return (z); case __LINE__:;\
        } while (0)
#define crReturnV       \
        do {\
            *crLine=__LINE__; return; case __LINE__:;\
        } while (0)
#define crStop(z)       do{ *crLine = 0; return (z); }while(0)
#define crStopV         do{ *crLine = 0; return; }while(0)
#define crWaitUntil(c)  do { crReturn(0); } while (!(c))
#define crWaitUntilV(c) do { crReturnV; } while (!(c))
#define crMaybeWaitUntil(c) do { while (!(c)) crReturn(0); } while (0)
#define crMaybeWaitUntilV(c) do { while (!(c)) crReturnV; } while (0)

#endif /* PUTTY_SSHCR_H */