/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.


 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SUNXI_RPROC_WDT_H
#define SUNXI_RPROC_WDT_H

#include <sunxi_hal_common.h>

struct sunxi_rproc_wdt;

enum sunxi_rproc_wdt_reset_type {
	RESET_DBG = 0,
	RESET_SYS,
	RESET_INT,
};

struct sunxi_rproc_wdt_param {
	void (*cb)(struct sunxi_rproc_wdt *wdt, void *priv);
	void *cb_priv;

	// wdt param
	void *reg_base;
	int irq_num;
	u32 timeout_ms;
	u32 reset_type;
};

struct sunxi_rproc_wdt {
	//spinlock_t lock;

	// res
	void *base;
	const struct sunxi_wdt_reg *regs;

	// wdt default param for start
	struct sunxi_rproc_wdt_param param;

	// pm
	u32 saved_timeout;
	u32 saved_rst_type;
};

// direct
int sunxi_rproc_wdt_set_timeout(struct sunxi_rproc_wdt *wdt, u32 timeout_ms);
int sunxi_rproc_wdt_get_timeout(struct sunxi_rproc_wdt *wdt, u32 *timeout_ms);
int sunxi_rproc_wdt_set_reset_type(struct sunxi_rproc_wdt *wdt, u32 type);
int sunxi_rproc_wdt_get_reset_type(struct sunxi_rproc_wdt *wdt, u32 *type);
int sunxi_rproc_wdt_is_enable(struct sunxi_rproc_wdt *wdt);

int sunxi_rproc_wdt_start(struct sunxi_rproc_wdt *wdt);
void sunxi_rproc_wdt_stop(struct sunxi_rproc_wdt *wdt);

int sunxi_rproc_wdt_suspend(struct sunxi_rproc_wdt *wdt);
int sunxi_rproc_wdt_resume(struct sunxi_rproc_wdt *wdt);

int sunxi_rproc_wdt_deinit(struct sunxi_rproc_wdt *wdt);
int sunxi_rproc_wdt_init(struct sunxi_rproc_wdt *wdt, struct sunxi_rproc_wdt_param *param);

#endif /* SUNXI_RPROC_WDT_H */
