/*
 * Copyright (C) 2019 Intel Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * BIOS Information
 * Vendor: Intel Corporation
 * Version: SE5C620.86B.02.01.0008.031920191559
 * Release Date: 03/19/2019
 * BIOS Revision: 0.0
 *
 * Base Board Information
 * Manufacturer: Intel Corporation
 * Product Name: S2600WF0
 * Version: H87179-853
 */

#ifndef PCI_DEVICES_H_
#define PCI_DEVICES_H_

#define HOST_BRIDGE                             .pbdf.bits = {.b = 0x00U, .d = 0x00U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_0                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x00U}, \
                                                .vbar_base[0] = 0x383ffff2c000UL
#define SYSTEM_PERIPHERAL_1                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x01U}, \
                                                .vbar_base[0] = 0x383ffff28000UL
#define SYSTEM_PERIPHERAL_2                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x02U}, \
                                                .vbar_base[0] = 0x383ffff24000UL
#define SYSTEM_PERIPHERAL_3                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x03U}, \
                                                .vbar_base[0] = 0x383ffff20000UL
#define SYSTEM_PERIPHERAL_4                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x04U}, \
                                                .vbar_base[0] = 0x383ffff1c000UL
#define SYSTEM_PERIPHERAL_5                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x05U}, \
                                                .vbar_base[0] = 0x383ffff18000UL
#define SYSTEM_PERIPHERAL_6                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x06U}, \
                                                .vbar_base[0] = 0x383ffff14000UL
#define SYSTEM_PERIPHERAL_7                     .pbdf.bits = {.b = 0x00U, .d = 0x04U, .f = 0x07U}, \
                                                .vbar_base[0] = 0x383ffff10000UL
#define SYSTEM_PERIPHERAL_8                     .pbdf.bits = {.b = 0x00U, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_9                     .pbdf.bits = {.b = 0x00U, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_10                    .pbdf.bits = {.b = 0x00U, .d = 0x08U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_11                    .pbdf.bits = {.b = 0x00U, .d = 0x08U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_12                    .pbdf.bits = {.b = 0x17U, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_13                    .pbdf.bits = {.b = 0x17U, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_14                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_15                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_16                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_17                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_18                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_19                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x05U}
#define SYSTEM_PERIPHERAL_20                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x06U}
#define SYSTEM_PERIPHERAL_21                    .pbdf.bits = {.b = 0x17U, .d = 0x08U, .f = 0x07U}
#define SYSTEM_PERIPHERAL_22                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_23                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_24                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_25                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_26                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_27                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x05U}
#define SYSTEM_PERIPHERAL_28                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x06U}
#define SYSTEM_PERIPHERAL_29                    .pbdf.bits = {.b = 0x17U, .d = 0x09U, .f = 0x07U}
#define SYSTEM_PERIPHERAL_30                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_31                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_32                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_33                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_34                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_35                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_36                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_37                    .pbdf.bits = {.b = 0x17U, .d = 0x0AU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_38                    .pbdf.bits = {.b = 0x17U, .d = 0x0BU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_39                    .pbdf.bits = {.b = 0x17U, .d = 0x0BU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_40                    .pbdf.bits = {.b = 0x17U, .d = 0x0BU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_41                    .pbdf.bits = {.b = 0x17U, .d = 0x0BU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_42                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_43                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_44                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_45                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_46                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_47                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_48                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_49                    .pbdf.bits = {.b = 0x17U, .d = 0x0EU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_50                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_51                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_52                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_53                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_54                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_55                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_56                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_57                    .pbdf.bits = {.b = 0x17U, .d = 0x0FU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_58                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_59                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_60                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_61                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_62                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_63                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x05U}
#define SYSTEM_PERIPHERAL_64                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x06U}
#define SYSTEM_PERIPHERAL_65                    .pbdf.bits = {.b = 0x17U, .d = 0x10U, .f = 0x07U}
#define SYSTEM_PERIPHERAL_66                    .pbdf.bits = {.b = 0x17U, .d = 0x11U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_67                    .pbdf.bits = {.b = 0x17U, .d = 0x11U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_68                    .pbdf.bits = {.b = 0x17U, .d = 0x11U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_69                    .pbdf.bits = {.b = 0x17U, .d = 0x11U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_70                    .pbdf.bits = {.b = 0x17U, .d = 0x1DU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_71                    .pbdf.bits = {.b = 0x17U, .d = 0x1DU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_72                    .pbdf.bits = {.b = 0x17U, .d = 0x1DU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_73                    .pbdf.bits = {.b = 0x17U, .d = 0x1DU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_74                    .pbdf.bits = {.b = 0x17U, .d = 0x1EU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_75                    .pbdf.bits = {.b = 0x17U, .d = 0x1EU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_76                    .pbdf.bits = {.b = 0x17U, .d = 0x1EU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_77                    .pbdf.bits = {.b = 0x17U, .d = 0x1EU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_78                    .pbdf.bits = {.b = 0x17U, .d = 0x1EU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_79                    .pbdf.bits = {.b = 0x17U, .d = 0x1EU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_80                    .pbdf.bits = {.b = 0x17U, .d = 0x1EU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_81                    .pbdf.bits = {.b = 0x3AU, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_82                    .pbdf.bits = {.b = 0x3AU, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_83                    .pbdf.bits = {.b = 0x3AU, .d = 0x08U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_84                    .pbdf.bits = {.b = 0x3AU, .d = 0x09U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_85                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_86                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_87                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_88                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_89                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_90                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_91                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_92                    .pbdf.bits = {.b = 0x3AU, .d = 0x0AU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_93                    .pbdf.bits = {.b = 0x3AU, .d = 0x0BU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_94                    .pbdf.bits = {.b = 0x3AU, .d = 0x0BU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_95                    .pbdf.bits = {.b = 0x3AU, .d = 0x0BU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_96                    .pbdf.bits = {.b = 0x3AU, .d = 0x0BU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_97                    .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_98                    .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_99                    .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_100                   .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_101                   .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_102                   .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_103                   .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_104                   .pbdf.bits = {.b = 0x3AU, .d = 0x0CU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_105                   .pbdf.bits = {.b = 0x3AU, .d = 0x0DU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_106                   .pbdf.bits = {.b = 0x3AU, .d = 0x0DU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_107                   .pbdf.bits = {.b = 0x3AU, .d = 0x0DU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_108                   .pbdf.bits = {.b = 0x3AU, .d = 0x0DU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_109                   .pbdf.bits = {.b = 0x5DU, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_110                   .pbdf.bits = {.b = 0x5DU, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_111                   .pbdf.bits = {.b = 0x5DU, .d = 0x0EU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_112                   .pbdf.bits = {.b = 0x5DU, .d = 0x0FU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_113                   .pbdf.bits = {.b = 0x5DU, .d = 0x10U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_114                   .pbdf.bits = {.b = 0x5DU, .d = 0x12U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_115                   .pbdf.bits = {.b = 0x5DU, .d = 0x15U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_116                   .pbdf.bits = {.b = 0x5DU, .d = 0x16U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_117                   .pbdf.bits = {.b = 0x5DU, .d = 0x16U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_118                   .pbdf.bits = {.b = 0x5DU, .d = 0x17U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_119                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x00U}, \
                                                .vbar_base[0] = 0x393ffff1c000UL
#define SYSTEM_PERIPHERAL_120                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x01U}, \
                                                .vbar_base[0] = 0x393ffff18000UL
#define SYSTEM_PERIPHERAL_121                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x02U}, \
                                                .vbar_base[0] = 0x393ffff14000UL
#define SYSTEM_PERIPHERAL_122                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x03U}, \
                                                .vbar_base[0] = 0x393ffff10000UL
#define SYSTEM_PERIPHERAL_123                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x04U}, \
                                                .vbar_base[0] = 0x393ffff0c000UL
#define SYSTEM_PERIPHERAL_124                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x05U}, \
                                                .vbar_base[0] = 0x393ffff08000UL
#define SYSTEM_PERIPHERAL_125                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x06U}, \
                                                .vbar_base[0] = 0x393ffff04000UL
#define SYSTEM_PERIPHERAL_126                   .pbdf.bits = {.b = 0x80U, .d = 0x04U, .f = 0x07U}, \
                                                .vbar_base[0] = 0x393ffff00000UL
#define SYSTEM_PERIPHERAL_127                   .pbdf.bits = {.b = 0x80U, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_128                   .pbdf.bits = {.b = 0x80U, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_129                   .pbdf.bits = {.b = 0x80U, .d = 0x08U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_130                   .pbdf.bits = {.b = 0x80U, .d = 0x08U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_131                   .pbdf.bits = {.b = 0x85U, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_132                   .pbdf.bits = {.b = 0x85U, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_133                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_134                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_135                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_136                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_137                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_138                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x05U}
#define SYSTEM_PERIPHERAL_139                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x06U}
#define SYSTEM_PERIPHERAL_140                   .pbdf.bits = {.b = 0x85U, .d = 0x08U, .f = 0x07U}
#define SYSTEM_PERIPHERAL_141                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_142                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_143                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_144                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_145                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_146                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x05U}
#define SYSTEM_PERIPHERAL_147                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x06U}
#define SYSTEM_PERIPHERAL_148                   .pbdf.bits = {.b = 0x85U, .d = 0x09U, .f = 0x07U}
#define SYSTEM_PERIPHERAL_149                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_150                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_151                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_152                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_153                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_154                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_155                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_156                   .pbdf.bits = {.b = 0x85U, .d = 0x0AU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_157                   .pbdf.bits = {.b = 0x85U, .d = 0x0BU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_158                   .pbdf.bits = {.b = 0x85U, .d = 0x0BU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_159                   .pbdf.bits = {.b = 0x85U, .d = 0x0BU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_160                   .pbdf.bits = {.b = 0x85U, .d = 0x0BU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_161                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_162                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_163                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_164                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_165                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_166                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_167                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_168                   .pbdf.bits = {.b = 0x85U, .d = 0x0EU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_169                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_170                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_171                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_172                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_173                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_174                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_175                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_176                   .pbdf.bits = {.b = 0x85U, .d = 0x0FU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_177                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_178                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_179                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_180                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_181                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_182                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x05U}
#define SYSTEM_PERIPHERAL_183                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x06U}
#define SYSTEM_PERIPHERAL_184                   .pbdf.bits = {.b = 0x85U, .d = 0x10U, .f = 0x07U}
#define SYSTEM_PERIPHERAL_185                   .pbdf.bits = {.b = 0x85U, .d = 0x11U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_186                   .pbdf.bits = {.b = 0x85U, .d = 0x11U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_187                   .pbdf.bits = {.b = 0x85U, .d = 0x11U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_188                   .pbdf.bits = {.b = 0x85U, .d = 0x11U, .f = 0x03U}
#define SYSTEM_PERIPHERAL_189                   .pbdf.bits = {.b = 0x85U, .d = 0x1DU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_190                   .pbdf.bits = {.b = 0x85U, .d = 0x1DU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_191                   .pbdf.bits = {.b = 0x85U, .d = 0x1DU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_192                   .pbdf.bits = {.b = 0x85U, .d = 0x1DU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_193                   .pbdf.bits = {.b = 0x85U, .d = 0x1EU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_194                   .pbdf.bits = {.b = 0x85U, .d = 0x1EU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_195                   .pbdf.bits = {.b = 0x85U, .d = 0x1EU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_196                   .pbdf.bits = {.b = 0x85U, .d = 0x1EU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_197                   .pbdf.bits = {.b = 0x85U, .d = 0x1EU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_198                   .pbdf.bits = {.b = 0x85U, .d = 0x1EU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_199                   .pbdf.bits = {.b = 0x85U, .d = 0x1EU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_200                   .pbdf.bits = {.b = 0xAEU, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_201                   .pbdf.bits = {.b = 0xAEU, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_202                   .pbdf.bits = {.b = 0xAEU, .d = 0x08U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_203                   .pbdf.bits = {.b = 0xAEU, .d = 0x09U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_204                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_205                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_206                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_207                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_208                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_209                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_210                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_211                   .pbdf.bits = {.b = 0xAEU, .d = 0x0AU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_212                   .pbdf.bits = {.b = 0xAEU, .d = 0x0BU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_213                   .pbdf.bits = {.b = 0xAEU, .d = 0x0BU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_214                   .pbdf.bits = {.b = 0xAEU, .d = 0x0BU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_215                   .pbdf.bits = {.b = 0xAEU, .d = 0x0BU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_216                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_217                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_218                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_219                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_220                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x04U}
#define SYSTEM_PERIPHERAL_221                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x05U}
#define SYSTEM_PERIPHERAL_222                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x06U}
#define SYSTEM_PERIPHERAL_223                   .pbdf.bits = {.b = 0xAEU, .d = 0x0CU, .f = 0x07U}
#define SYSTEM_PERIPHERAL_224                   .pbdf.bits = {.b = 0xAEU, .d = 0x0DU, .f = 0x00U}
#define SYSTEM_PERIPHERAL_225                   .pbdf.bits = {.b = 0xAEU, .d = 0x0DU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_226                   .pbdf.bits = {.b = 0xAEU, .d = 0x0DU, .f = 0x02U}
#define SYSTEM_PERIPHERAL_227                   .pbdf.bits = {.b = 0xAEU, .d = 0x0DU, .f = 0x03U}
#define SYSTEM_PERIPHERAL_228                   .pbdf.bits = {.b = 0xD7U, .d = 0x05U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_229                   .pbdf.bits = {.b = 0xD7U, .d = 0x05U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_230                   .pbdf.bits = {.b = 0xD7U, .d = 0x0EU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_231                   .pbdf.bits = {.b = 0xD7U, .d = 0x0FU, .f = 0x01U}
#define SYSTEM_PERIPHERAL_232                   .pbdf.bits = {.b = 0xD7U, .d = 0x10U, .f = 0x01U}
#define SYSTEM_PERIPHERAL_233                   .pbdf.bits = {.b = 0xD7U, .d = 0x12U, .f = 0x02U}
#define SYSTEM_PERIPHERAL_234                   .pbdf.bits = {.b = 0xD7U, .d = 0x15U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_235                   .pbdf.bits = {.b = 0xD7U, .d = 0x16U, .f = 0x00U}
#define SYSTEM_PERIPHERAL_236                   .pbdf.bits = {.b = 0xD7U, .d = 0x16U, .f = 0x04U}
#define SYSTEM_PERIPHERAL_237                   .pbdf.bits = {.b = 0xD7U, .d = 0x17U, .f = 0x00U}
#define PIC_0                                   .pbdf.bits = {.b = 0x00U, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0x9230a000UL
#define PIC_1                                   .pbdf.bits = {.b = 0x17U, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0x9d800000UL
#define PIC_2                                   .pbdf.bits = {.b = 0x3AU, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0xac600000UL
#define PIC_3                                   .pbdf.bits = {.b = 0x5DU, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0xb8900000UL
#define PIC_4                                   .pbdf.bits = {.b = 0x80U, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0xc6200000UL
#define PIC_5                                   .pbdf.bits = {.b = 0x85U, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0xd3d00000UL
#define PIC_6                                   .pbdf.bits = {.b = 0xAEU, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0xe1000000UL
#define PIC_7                                   .pbdf.bits = {.b = 0xD7U, .d = 0x05U, .f = 0x04U}, \
                                                .vbar_base[0] = 0xef500000UL
#define PERFORMANCE_COUNTERS_0                  .pbdf.bits = {.b = 0x00U, .d = 0x08U, .f = 0x01U}
#define PERFORMANCE_COUNTERS_1                  .pbdf.bits = {.b = 0x5DU, .d = 0x0EU, .f = 0x00U}
#define PERFORMANCE_COUNTERS_2                  .pbdf.bits = {.b = 0x5DU, .d = 0x0FU, .f = 0x00U}
#define PERFORMANCE_COUNTERS_3                  .pbdf.bits = {.b = 0x5DU, .d = 0x10U, .f = 0x00U}
#define PERFORMANCE_COUNTERS_4                  .pbdf.bits = {.b = 0x5DU, .d = 0x12U, .f = 0x00U}
#define PERFORMANCE_COUNTERS_5                  .pbdf.bits = {.b = 0x5DU, .d = 0x12U, .f = 0x01U}
#define PERFORMANCE_COUNTERS_6                  .pbdf.bits = {.b = 0x5DU, .d = 0x12U, .f = 0x04U}
#define PERFORMANCE_COUNTERS_7                  .pbdf.bits = {.b = 0x5DU, .d = 0x12U, .f = 0x05U}
#define PERFORMANCE_COUNTERS_8                  .pbdf.bits = {.b = 0x80U, .d = 0x08U, .f = 0x01U}
#define PERFORMANCE_COUNTERS_9                  .pbdf.bits = {.b = 0xD7U, .d = 0x0EU, .f = 0x00U}
#define PERFORMANCE_COUNTERS_10                 .pbdf.bits = {.b = 0xD7U, .d = 0x0FU, .f = 0x00U}
#define PERFORMANCE_COUNTERS_11                 .pbdf.bits = {.b = 0xD7U, .d = 0x10U, .f = 0x00U}
#define PERFORMANCE_COUNTERS_12                 .pbdf.bits = {.b = 0xD7U, .d = 0x12U, .f = 0x00U}
#define PERFORMANCE_COUNTERS_13                 .pbdf.bits = {.b = 0xD7U, .d = 0x12U, .f = 0x01U}
#define PERFORMANCE_COUNTERS_14                 .pbdf.bits = {.b = 0xD7U, .d = 0x12U, .f = 0x04U}
#define PERFORMANCE_COUNTERS_15                 .pbdf.bits = {.b = 0xD7U, .d = 0x12U, .f = 0x05U}
#define UNASSIGNED_CLASS_0                      .pbdf.bits = {.b = 0x00U, .d = 0x11U, .f = 0x00U}
#define UNASSIGNED_CLASS_1                      .pbdf.bits = {.b = 0x00U, .d = 0x11U, .f = 0x01U}
#define SATA_CONTROLLER_0                       .pbdf.bits = {.b = 0x00U, .d = 0x11U, .f = 0x05U}, \
                                                .vbar_base[0] = 0x92306000UL, \
                                                .vbar_base[1] = 0x92309000UL, \
                                                .vbar_base[5] = 0x92280000UL
#define SATA_CONTROLLER_1                       .pbdf.bits = {.b = 0x00U, .d = 0x17U, .f = 0x00U}, \
                                                .vbar_base[0] = 0x92304000UL, \
                                                .vbar_base[1] = 0x92308000UL, \
                                                .vbar_base[5] = 0x92200000UL
#define USB_CONTROLLER_0                        .pbdf.bits = {.b = 0x00U, .d = 0x14U, .f = 0x00U}, \
                                                .vbar_base[0] = 0x383ffff00000UL
#define SIGNAL_PROCESSING_CONTROLLER_0          .pbdf.bits = {.b = 0x00U, .d = 0x14U, .f = 0x02U}, \
                                                .vbar_base[0] = 0x383ffff34000UL
#define COMMUNICATION_CONTROLLER_0              .pbdf.bits = {.b = 0x00U, .d = 0x16U, .f = 0x00U}, \
                                                .vbar_base[0] = 0x383ffff33000UL
#define COMMUNICATION_CONTROLLER_1              .pbdf.bits = {.b = 0x00U, .d = 0x16U, .f = 0x01U}, \
                                                .vbar_base[0] = 0x383ffff32000UL
#define COMMUNICATION_CONTROLLER_2              .pbdf.bits = {.b = 0x00U, .d = 0x16U, .f = 0x04U}, \
                                                .vbar_base[0] = 0x383ffff31000UL
#define PCI_BRIDGE_0                            .pbdf.bits = {.b = 0x00U, .d = 0x1CU, .f = 0x00U}
#define PCI_BRIDGE_1                            .pbdf.bits = {.b = 0x00U, .d = 0x1DU, .f = 0x00U}
#define PCI_BRIDGE_2                            .pbdf.bits = {.b = 0x01U, .d = 0x00U, .f = 0x00U}
#define PCI_BRIDGE_3                            .pbdf.bits = {.b = 0x3AU, .d = 0x00U, .f = 0x00U}
#define PCI_BRIDGE_4                            .pbdf.bits = {.b = 0x3BU, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0xac500000UL
#define PCI_BRIDGE_5                            .pbdf.bits = {.b = 0x3CU, .d = 0x03U, .f = 0x00U}
#define PCI_BRIDGE_6                            .pbdf.bits = {.b = 0x5DU, .d = 0x02U, .f = 0x00U}
#define PCI_BRIDGE_7                            .pbdf.bits = {.b = 0x5DU, .d = 0x03U, .f = 0x00U}
#define PCI_BRIDGE_8                            .pbdf.bits = {.b = 0x80U, .d = 0x00U, .f = 0x00U}
#define PCI_BRIDGE_9                            .pbdf.bits = {.b = 0x85U, .d = 0x02U, .f = 0x00U}
#define PCI_BRIDGE_10                           .pbdf.bits = {.b = 0xD7U, .d = 0x00U, .f = 0x00U}
#define PCI_BRIDGE_11                           .pbdf.bits = {.b = 0xD7U, .d = 0x01U, .f = 0x00U}
#define PCI_BRIDGE_12                           .pbdf.bits = {.b = 0xD7U, .d = 0x02U, .f = 0x00U}
#define ISA_BRIDGE_0                            .pbdf.bits = {.b = 0x00U, .d = 0x1FU, .f = 0x00U}
#define MEMORY_CONTROLLER_0                     .pbdf.bits = {.b = 0x00U, .d = 0x1FU, .f = 0x02U}, \
                                                .vbar_base[0] = 0x92300000UL
#define SMBUS_0                                 .pbdf.bits = {.b = 0x00U, .d = 0x1FU, .f = 0x04U}, \
                                                .vbar_base[0] = 0x383ffff30000UL
#define SERIAL_BUS_CONTROLLER_0                 .pbdf.bits = {.b = 0x00U, .d = 0x1FU, .f = 0x05U}, \
                                                .vbar_base[0] = 0xfe010000UL
#define VGA_COMPATIBLE_CONTROLLER_0             .pbdf.bits = {.b = 0x02U, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0x91000000UL, \
                                                .vbar_base[1] = 0x92000000UL
#define Non_Volatile_memory_controller_0        .pbdf.bits = {.b = 0x03U, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0x92100000UL
#define Non_Volatile_memory_controller_1        .pbdf.bits = {.b = 0x5EU, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0xb8800000UL
#define ETHERNET_CONTROLLER_0                   .pbdf.bits = {.b = 0x3DU, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0xac000000UL, \
                                                .vbar_base[3] = 0xac408000UL
#define ETHERNET_CONTROLLER_1                   .pbdf.bits = {.b = 0x81U, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0xc6000000UL, \
                                                .vbar_base[3] = 0xc6100000UL
#define ETHERNET_CONTROLLER_2                   .pbdf.bits = {.b = 0xDAU, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0xef300000UL, \
                                                .vbar_base[4] = 0xef004000UL, \
                                                .vbar_base[3] = 0xef400000UL
#define ETHERNET_CONTROLLER_3                   .pbdf.bits = {.b = 0xDAU, .d = 0x00U, .f = 0x01U}, \
                                                .vbar_base[0] = 0xef100000UL, \
                                                .vbar_base[4] = 0xef000000UL, \
                                                .vbar_base[3] = 0xef200000UL
#define SERIAL_CONTROLLER_0                     .pbdf.bits = {.b = 0x86U, .d = 0x00U, .f = 0x00U}, \
                                                .vbar_base[0] = 0xd3c00000UL, \
                                                .vbar_base[1] = 0xd3a00000UL, \
                                                .vbar_base[2] = 0xd3800000UL

#endif /* PCI_DEVICES_H_ */
