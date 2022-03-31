/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H               

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'BP1' to the base of port 'bp1'
#ifndef BP1
#error BP1 is undefined. It needs to be set to the port base address
#endif


#define BP1_REG_POFFSET                 0x0
#define BP1_REG_AIC_SMR_POFFSET         0x0
#define BP1_REG_AIC_SMR(_MMR_INDEX)     (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_SMR_POFFSET + ((_MMR_INDEX) * 0x4))

#define BP1_REG_AIC_SVR_POFFSET         0x80
#define BP1_REG_AIC_SVR(_MMR_INDEX)     (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_SVR_POFFSET + ((_MMR_INDEX) * 0x4))

#define BP1_REG_AIC_IVR_POFFSET         0x100
#define BP1_REG_AIC_IVR                 (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_IVR_POFFSET)

#define BP1_REG_AIC_FVR_POFFSET         0x104
#define BP1_REG_AIC_FVR                 (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_FVR_POFFSET)

#define BP1_REG_AIC_ISR_POFFSET         0x108
#define BP1_REG_AIC_ISR                 (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_ISR_POFFSET)
#define BP1_REG_AIC_ISR_IRQID           0x1f
#define BP1_REG_AIC_ISR_IRQID_GET(_v)   (_v & 0x1f)

#define BP1_REG_AIC_IPR_POFFSET         0x10c
#define BP1_REG_AIC_IPR                 (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_IPR_POFFSET)
#define BP1_REG_AIC_IPR_IRQ2            (0x1 << 18)
#define BP1_REG_AIC_IPR_IRQ2_GET(_v)    ((_v >> 18) & 0x1)
#define BP1_REG_AIC_IPR_IRQ1            (0x1 << 17)
#define BP1_REG_AIC_IPR_IRQ1_GET(_v)    ((_v >> 17) & 0x1)
#define BP1_REG_AIC_IPR_IRQ0            (0x1 << 16)
#define BP1_REG_AIC_IPR_IRQ0_GET(_v)    ((_v >> 16) & 0x1)
#define BP1_REG_AIC_IPR_PIOIRQ          (0x1 << 8)
#define BP1_REG_AIC_IPR_PIOIRQ_GET(_v)  ((_v >> 8) & 0x1)
#define BP1_REG_AIC_IPR_WDIRQ           (0x1 << 7)
#define BP1_REG_AIC_IPR_WDIRQ_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_AIC_IPR_TC2IRQ          (0x1 << 6)
#define BP1_REG_AIC_IPR_TC2IRQ_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_AIC_IPR_TC1IRQ          (0x1 << 5)
#define BP1_REG_AIC_IPR_TC1IRQ_GET(_v)  ((_v >> 5) & 0x1)
#define BP1_REG_AIC_IPR_TC0IRQ          (0x1 << 4)
#define BP1_REG_AIC_IPR_TC0IRQ_GET(_v)  ((_v >> 4) & 0x1)
#define BP1_REG_AIC_IPR_US1IRQ          (0x1 << 3)
#define BP1_REG_AIC_IPR_US1IRQ_GET(_v)  ((_v >> 3) & 0x1)
#define BP1_REG_AIC_IPR_US0IRQ          (0x1 << 2)
#define BP1_REG_AIC_IPR_US0IRQ_GET(_v)  ((_v >> 2) & 0x1)
#define BP1_REG_AIC_IPR_SWIRQ           (0x1 << 1)
#define BP1_REG_AIC_IPR_SWIRQ_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_AIC_IPR_FIQ             0x1
#define BP1_REG_AIC_IPR_FIQ_GET(_v)     (_v & 0x1)

#define BP1_REG_AIC_IMR_POFFSET         0x110
#define BP1_REG_AIC_IMR                 (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_IMR_POFFSET)
#define BP1_REG_AIC_IMR_IRQ2            (0x1 << 18)
#define BP1_REG_AIC_IMR_IRQ2_GET(_v)    ((_v >> 18) & 0x1)
#define BP1_REG_AIC_IMR_IRQ1            (0x1 << 17)
#define BP1_REG_AIC_IMR_IRQ1_GET(_v)    ((_v >> 17) & 0x1)
#define BP1_REG_AIC_IMR_IRQ0            (0x1 << 16)
#define BP1_REG_AIC_IMR_IRQ0_GET(_v)    ((_v >> 16) & 0x1)
#define BP1_REG_AIC_IMR_PIOIRQ          (0x1 << 8)
#define BP1_REG_AIC_IMR_PIOIRQ_GET(_v)  ((_v >> 8) & 0x1)
#define BP1_REG_AIC_IMR_WDIRQ           (0x1 << 7)
#define BP1_REG_AIC_IMR_WDIRQ_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_AIC_IMR_TC2IRQ          (0x1 << 6)
#define BP1_REG_AIC_IMR_TC2IRQ_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_AIC_IMR_TC1IRQ          (0x1 << 5)
#define BP1_REG_AIC_IMR_TC1IRQ_GET(_v)  ((_v >> 5) & 0x1)
#define BP1_REG_AIC_IMR_TC0IRQ          (0x1 << 4)
#define BP1_REG_AIC_IMR_TC0IRQ_GET(_v)  ((_v >> 4) & 0x1)
#define BP1_REG_AIC_IMR_US1IRQ          (0x1 << 3)
#define BP1_REG_AIC_IMR_US1IRQ_GET(_v)  ((_v >> 3) & 0x1)
#define BP1_REG_AIC_IMR_US0IRQ          (0x1 << 2)
#define BP1_REG_AIC_IMR_US0IRQ_GET(_v)  ((_v >> 2) & 0x1)
#define BP1_REG_AIC_IMR_SWIRQ           (0x1 << 1)
#define BP1_REG_AIC_IMR_SWIRQ_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_AIC_IMR_FIQ             0x1
#define BP1_REG_AIC_IMR_FIQ_GET(_v)     (_v & 0x1)

#define BP1_REG_AIC_CISR_POFFSET        0x114
#define BP1_REG_AIC_CISR                (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_CISR_POFFSET)
#define BP1_REG_AIC_CISR_NIRQ           (0x1 << 1)
#define BP1_REG_AIC_CISR_NIRQ_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_AIC_CISR_NFIQ           0x1
#define BP1_REG_AIC_CISR_NFIQ_GET(_v)   (_v & 0x1)

#define BP1_REG_AIC_IECR_POFFSET        0x120
#define BP1_REG_AIC_IECR                (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_IECR_POFFSET)
#define BP1_REG_AIC_IECR_IRQ2           (0x1 << 18)
#define BP1_REG_AIC_IECR_IRQ2_GET(_v)   ((_v >> 18) & 0x1)
#define BP1_REG_AIC_IECR_IRQ1           (0x1 << 17)
#define BP1_REG_AIC_IECR_IRQ1_GET(_v)   ((_v >> 17) & 0x1)
#define BP1_REG_AIC_IECR_IRQ0           (0x1 << 16)
#define BP1_REG_AIC_IECR_IRQ0_GET(_v)   ((_v >> 16) & 0x1)
#define BP1_REG_AIC_IECR_PIOIRQ         (0x1 << 8)
#define BP1_REG_AIC_IECR_PIOIRQ_GET(_v)  ((_v >> 8) & 0x1)
#define BP1_REG_AIC_IECR_WDIRQ          (0x1 << 7)
#define BP1_REG_AIC_IECR_WDIRQ_GET(_v)  ((_v >> 7) & 0x1)
#define BP1_REG_AIC_IECR_TC2IRQ         (0x1 << 6)
#define BP1_REG_AIC_IECR_TC2IRQ_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_AIC_IECR_TC1IRQ         (0x1 << 5)
#define BP1_REG_AIC_IECR_TC1IRQ_GET(_v)  ((_v >> 5) & 0x1)
#define BP1_REG_AIC_IECR_TC0IRQ         (0x1 << 4)
#define BP1_REG_AIC_IECR_TC0IRQ_GET(_v)  ((_v >> 4) & 0x1)
#define BP1_REG_AIC_IECR_US1IRQ         (0x1 << 3)
#define BP1_REG_AIC_IECR_US1IRQ_GET(_v)  ((_v >> 3) & 0x1)
#define BP1_REG_AIC_IECR_US0IRQ         (0x1 << 2)
#define BP1_REG_AIC_IECR_US0IRQ_GET(_v)  ((_v >> 2) & 0x1)
#define BP1_REG_AIC_IECR_SWIRQ          (0x1 << 1)
#define BP1_REG_AIC_IECR_SWIRQ_GET(_v)  ((_v >> 1) & 0x1)
#define BP1_REG_AIC_IECR_FIQ            0x1
#define BP1_REG_AIC_IECR_FIQ_GET(_v)    (_v & 0x1)

#define BP1_REG_AIC_IDCR_POFFSET        0x124
#define BP1_REG_AIC_IDCR                (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_IDCR_POFFSET)
#define BP1_REG_AIC_IDCR_IRQ2           (0x1 << 18)
#define BP1_REG_AIC_IDCR_IRQ2_GET(_v)   ((_v >> 18) & 0x1)
#define BP1_REG_AIC_IDCR_IRQ1           (0x1 << 17)
#define BP1_REG_AIC_IDCR_IRQ1_GET(_v)   ((_v >> 17) & 0x1)
#define BP1_REG_AIC_IDCR_IRQ0           (0x1 << 16)
#define BP1_REG_AIC_IDCR_IRQ0_GET(_v)   ((_v >> 16) & 0x1)
#define BP1_REG_AIC_IDCR_PIOIRQ         (0x1 << 8)
#define BP1_REG_AIC_IDCR_PIOIRQ_GET(_v)  ((_v >> 8) & 0x1)
#define BP1_REG_AIC_IDCR_WDIRQ          (0x1 << 7)
#define BP1_REG_AIC_IDCR_WDIRQ_GET(_v)  ((_v >> 7) & 0x1)
#define BP1_REG_AIC_IDCR_TC2IRQ         (0x1 << 6)
#define BP1_REG_AIC_IDCR_TC2IRQ_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_AIC_IDCR_TC1IRQ         (0x1 << 5)
#define BP1_REG_AIC_IDCR_TC1IRQ_GET(_v)  ((_v >> 5) & 0x1)
#define BP1_REG_AIC_IDCR_TC0IRQ         (0x1 << 4)
#define BP1_REG_AIC_IDCR_TC0IRQ_GET(_v)  ((_v >> 4) & 0x1)
#define BP1_REG_AIC_IDCR_US1IRQ         (0x1 << 3)
#define BP1_REG_AIC_IDCR_US1IRQ_GET(_v)  ((_v >> 3) & 0x1)
#define BP1_REG_AIC_IDCR_US0IRQ         (0x1 << 2)
#define BP1_REG_AIC_IDCR_US0IRQ_GET(_v)  ((_v >> 2) & 0x1)
#define BP1_REG_AIC_IDCR_SWIRQ          (0x1 << 1)
#define BP1_REG_AIC_IDCR_SWIRQ_GET(_v)  ((_v >> 1) & 0x1)
#define BP1_REG_AIC_IDCR_FIQ            0x1
#define BP1_REG_AIC_IDCR_FIQ_GET(_v)    (_v & 0x1)

#define BP1_REG_AIC_ICCR_POFFSET        0x128
#define BP1_REG_AIC_ICCR                (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_ICCR_POFFSET)
#define BP1_REG_AIC_ICCR_IRQ2           (0x1 << 18)
#define BP1_REG_AIC_ICCR_IRQ2_GET(_v)   ((_v >> 18) & 0x1)
#define BP1_REG_AIC_ICCR_IRQ1           (0x1 << 17)
#define BP1_REG_AIC_ICCR_IRQ1_GET(_v)   ((_v >> 17) & 0x1)
#define BP1_REG_AIC_ICCR_IRQ0           (0x1 << 16)
#define BP1_REG_AIC_ICCR_IRQ0_GET(_v)   ((_v >> 16) & 0x1)
#define BP1_REG_AIC_ICCR_PIOIRQ         (0x1 << 8)
#define BP1_REG_AIC_ICCR_PIOIRQ_GET(_v)  ((_v >> 8) & 0x1)
#define BP1_REG_AIC_ICCR_WDIRQ          (0x1 << 7)
#define BP1_REG_AIC_ICCR_WDIRQ_GET(_v)  ((_v >> 7) & 0x1)
#define BP1_REG_AIC_ICCR_TC2IRQ         (0x1 << 6)
#define BP1_REG_AIC_ICCR_TC2IRQ_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_AIC_ICCR_TC1IRQ         (0x1 << 5)
#define BP1_REG_AIC_ICCR_TC1IRQ_GET(_v)  ((_v >> 5) & 0x1)
#define BP1_REG_AIC_ICCR_TC0IRQ         (0x1 << 4)
#define BP1_REG_AIC_ICCR_TC0IRQ_GET(_v)  ((_v >> 4) & 0x1)
#define BP1_REG_AIC_ICCR_US1IRQ         (0x1 << 3)
#define BP1_REG_AIC_ICCR_US1IRQ_GET(_v)  ((_v >> 3) & 0x1)
#define BP1_REG_AIC_ICCR_US0IRQ         (0x1 << 2)
#define BP1_REG_AIC_ICCR_US0IRQ_GET(_v)  ((_v >> 2) & 0x1)
#define BP1_REG_AIC_ICCR_SWIRQ          (0x1 << 1)
#define BP1_REG_AIC_ICCR_SWIRQ_GET(_v)  ((_v >> 1) & 0x1)
#define BP1_REG_AIC_ICCR_FIQ            0x1
#define BP1_REG_AIC_ICCR_FIQ_GET(_v)    (_v & 0x1)

#define BP1_REG_AIC_ISCR_POFFSET        0x12c
#define BP1_REG_AIC_ISCR                (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_ISCR_POFFSET)
#define BP1_REG_AIC_ISCR_IRQ2           (0x1 << 18)
#define BP1_REG_AIC_ISCR_IRQ2_GET(_v)   ((_v >> 18) & 0x1)
#define BP1_REG_AIC_ISCR_IRQ1           (0x1 << 17)
#define BP1_REG_AIC_ISCR_IRQ1_GET(_v)   ((_v >> 17) & 0x1)
#define BP1_REG_AIC_ISCR_IRQ0           (0x1 << 16)
#define BP1_REG_AIC_ISCR_IRQ0_GET(_v)   ((_v >> 16) & 0x1)
#define BP1_REG_AIC_ISCR_PIOIRQ         (0x1 << 8)
#define BP1_REG_AIC_ISCR_PIOIRQ_GET(_v)  ((_v >> 8) & 0x1)
#define BP1_REG_AIC_ISCR_WDIRQ          (0x1 << 7)
#define BP1_REG_AIC_ISCR_WDIRQ_GET(_v)  ((_v >> 7) & 0x1)
#define BP1_REG_AIC_ISCR_TC2IRQ         (0x1 << 6)
#define BP1_REG_AIC_ISCR_TC2IRQ_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_AIC_ISCR_TC1IRQ         (0x1 << 5)
#define BP1_REG_AIC_ISCR_TC1IRQ_GET(_v)  ((_v >> 5) & 0x1)
#define BP1_REG_AIC_ISCR_TC0IRQ         (0x1 << 4)
#define BP1_REG_AIC_ISCR_TC0IRQ_GET(_v)  ((_v >> 4) & 0x1)
#define BP1_REG_AIC_ISCR_US1IRQ         (0x1 << 3)
#define BP1_REG_AIC_ISCR_US1IRQ_GET(_v)  ((_v >> 3) & 0x1)
#define BP1_REG_AIC_ISCR_US0IRQ         (0x1 << 2)
#define BP1_REG_AIC_ISCR_US0IRQ_GET(_v)  ((_v >> 2) & 0x1)
#define BP1_REG_AIC_ISCR_SWIRQ          (0x1 << 1)
#define BP1_REG_AIC_ISCR_SWIRQ_GET(_v)  ((_v >> 1) & 0x1)
#define BP1_REG_AIC_ISCR_FIQ            0x1
#define BP1_REG_AIC_ISCR_FIQ_GET(_v)    (_v & 0x1)

#define BP1_REG_AIC_EOICR_POFFSET       0x130
#define BP1_REG_AIC_EOICR               (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_EOICR_POFFSET)

#define BP1_REG_AIC_SPU_POFFSET         0x134
#define BP1_REG_AIC_SPU                 (BP1 + BP1_REG_POFFSET + BP1_REG_AIC_SPU_POFFSET)


#endif
