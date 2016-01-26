#ifndef NT2_LINALG_FUNCTIONS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_HPP_INCLUDED

#include <nt2/linalg/include/functions/balance.hpp>
#include <nt2/linalg/include/functions/cdf2rdf.hpp>
#include <nt2/linalg/include/functions/chol.hpp>
#include <nt2/linalg/include/functions/clinsolve.hpp>
#include <nt2/linalg/include/functions/cond.hpp>
#include <nt2/linalg/include/functions/cov.hpp>
#include <nt2/linalg/include/functions/cross.hpp>
#include <nt2/linalg/include/functions/csne.hpp>
#include <nt2/linalg/include/functions/det.hpp>
#include <nt2/linalg/include/functions/expm.hpp>
#include <nt2/linalg/include/functions/eyeminus.hpp>
#include <nt2/linalg/include/functions/eyeplus.hpp>
#include <nt2/linalg/include/functions/funm.hpp>
#include <nt2/linalg/include/functions/gbcon.hpp>
#include <nt2/linalg/include/functions/gbsv.hpp>
#include <nt2/linalg/include/functions/gebak.hpp>
#include <nt2/linalg/include/functions/gebal.hpp>
#include <nt2/linalg/include/functions/gecon.hpp>
#include <nt2/linalg/include/functions/geesx.hpp>
#include <nt2/linalg/include/functions/geesx1.hpp>
#include <nt2/linalg/include/functions/geesx_no_w.hpp>
#include <nt2/linalg/include/functions/geesxw.hpp>
#include <nt2/linalg/include/functions/geev_w.hpp>
#include <nt2/linalg/include/functions/geev_wvr.hpp>
#include <nt2/linalg/include/functions/geev_wvrvl.hpp>
#include <nt2/linalg/include/functions/gels.hpp>
#include <nt2/linalg/include/functions/gelsy.hpp>
#include <nt2/linalg/include/functions/gemsv.hpp>
#include <nt2/linalg/include/functions/geneig.hpp>
#include <nt2/linalg/include/functions/geqp3.hpp>
#include <nt2/linalg/include/functions/geqrf.hpp>
#include <nt2/linalg/include/functions/gesv.hpp>
#include <nt2/linalg/include/functions/gesvd.hpp>
#include <nt2/linalg/include/functions/gesvd_w.hpp>
#include <nt2/linalg/include/functions/gesvx.hpp>
#include <nt2/linalg/include/functions/getrf.hpp>
#include <nt2/linalg/include/functions/getri.hpp>
#include <nt2/linalg/include/functions/ggev_w.hpp>
#include <nt2/linalg/include/functions/ggev_wvr.hpp>
#include <nt2/linalg/include/functions/ggev_wvrvl.hpp>
#include <nt2/linalg/include/functions/gqr.hpp>
#include <nt2/linalg/include/functions/hsev.hpp>
#include <nt2/linalg/include/functions/hsev_w.hpp>
#include <nt2/linalg/include/functions/hsev_wu.hpp>
#include <nt2/linalg/include/functions/inv.hpp>
#include <nt2/linalg/include/functions/langb.hpp>
#include <nt2/linalg/include/functions/lange.hpp>
#include <nt2/linalg/include/functions/lansy.hpp>
#include <nt2/linalg/include/functions/laswp.hpp>
#include <nt2/linalg/include/functions/ldl.hpp>
#include <nt2/linalg/include/functions/linsolve.hpp>
#include <nt2/linalg/include/functions/llspgen.hpp>
#include <nt2/linalg/include/functions/logm.hpp>
#include <nt2/linalg/include/functions/lu.hpp>
#include <nt2/linalg/include/functions/lyapunov.hpp>
#include <nt2/linalg/include/functions/mcsne.hpp>
#include <nt2/linalg/include/functions/minuseye.hpp>
#include <nt2/linalg/include/functions/mldivide.hpp>
#include <nt2/linalg/include/functions/mlinsolve.hpp>
#include <nt2/linalg/include/functions/mnorm.hpp>
#include <nt2/linalg/include/functions/mnorm1.hpp>
#include <nt2/linalg/include/functions/mnormest.hpp>
#include <nt2/linalg/include/functions/mnormfro.hpp>
#include <nt2/linalg/include/functions/mnorminf.hpp>
#include <nt2/linalg/include/functions/mpower.hpp>
#include <nt2/linalg/include/functions/mqr.hpp>
#include <nt2/linalg/include/functions/mtimes.hpp>
#include <nt2/linalg/include/functions/norm.hpp>
#include <nt2/linalg/include/functions/nseig.hpp>
#include <nt2/linalg/include/functions/null.hpp>
#include <nt2/linalg/include/functions/options.hpp>
#include <nt2/linalg/include/functions/orth.hpp>
#include <nt2/linalg/include/functions/pinv.hpp>
#include <nt2/linalg/include/functions/planerot.hpp>
#include <nt2/linalg/include/functions/plinsolve.hpp>
#include <nt2/linalg/include/functions/pluseye.hpp>
#include <nt2/linalg/include/functions/pocon.hpp>
#include <nt2/linalg/include/functions/poly.hpp>
#include <nt2/linalg/include/functions/pomsv.hpp>
#include <nt2/linalg/include/functions/posv.hpp>
#include <nt2/linalg/include/functions/posvx.hpp>
#include <nt2/linalg/include/functions/potrf.hpp>
#include <nt2/linalg/include/functions/qr.hpp>
#include <nt2/linalg/include/functions/qrdelete.hpp>
#include <nt2/linalg/include/functions/qrinsert.hpp>
#include <nt2/linalg/include/functions/rank.hpp>
#include <nt2/linalg/include/functions/rcond.hpp>
#include <nt2/linalg/include/functions/rot90.hpp>
#include <nt2/linalg/include/functions/rref.hpp>
#include <nt2/linalg/include/functions/rsf2csf.hpp>
#include <nt2/linalg/include/functions/schur.hpp>
#include <nt2/linalg/include/functions/signm.hpp>
#include <nt2/linalg/include/functions/sne.hpp>
#include <nt2/linalg/include/functions/sqrtm.hpp>
#include <nt2/linalg/include/functions/subspace.hpp>
#include <nt2/linalg/include/functions/svd.hpp>
#include <nt2/linalg/include/functions/sycon.hpp>
#include <nt2/linalg/include/functions/sylvester.hpp>
#include <nt2/linalg/include/functions/symeig.hpp>
#include <nt2/linalg/include/functions/sysv.hpp>
#include <nt2/linalg/include/functions/sysvx.hpp>
#include <nt2/linalg/include/functions/tksolve.hpp>
#include <nt2/linalg/include/functions/trace.hpp>
#include <nt2/linalg/include/functions/trsm.hpp>
#include <nt2/linalg/include/functions/trsolve.hpp>
#include <nt2/linalg/include/functions/vecnorm.hpp>
#include <nt2/linalg/include/functions/xerbla.hpp>

#endif
