#pragma once

#include <glib-object.h>
#include "gw-types.h"

G_BEGIN_DECLS

typedef enum
{
    /* Unknown.  */
    GW_TREE_KIND_UNKNOWN,

    /* An internal signal.  */
    GW_TREE_KIND_SIGNAL,

    /* An in/out/inout signal.  */
    GW_TREE_KIND_IN,
    GW_TREE_KIND_OUT,
    GW_TREE_KIND_INOUT,

    /* An element of a vector.  */
    GW_TREE_KIND_VECTOREL,
    /* An element of a record.  */
    GW_TREE_KIND_RECORDEL,

    /* A Subinstance.  */
    GW_TREE_KIND_INSTANCE,

    /* A package (somewhat VHDL specific ?).  */
    GW_TREE_KIND_PACKAGE,

    /* A base (source file).  Not yet implemented.  */
    GW_TREE_KIND_BASE,

    /* Verilog/SV scope types */
    GW_TREE_KIND_VCD_ST_MODULE,
    GW_TREE_KIND_VCD_ST_TASK,
    GW_TREE_KIND_VCD_ST_FUNCTION,
    GW_TREE_KIND_VCD_ST_BEGIN,
    GW_TREE_KIND_VCD_ST_FORK,
    GW_TREE_KIND_VCD_ST_GENERATE,
    GW_TREE_KIND_VCD_ST_STRUCT,
    GW_TREE_KIND_VCD_ST_UNION,
    GW_TREE_KIND_VCD_ST_CLASS,
    GW_TREE_KIND_VCD_ST_INTERFACE,
    GW_TREE_KIND_VCD_ST_PACKAGE,
    GW_TREE_KIND_VCD_ST_PROGRAM,

    /* GHW VHDL scope types */
    GW_TREE_KIND_VHDL_ST_DESIGN,
    GW_TREE_KIND_VHDL_ST_BLOCK,
    GW_TREE_KIND_VHDL_ST_GENIF,
    GW_TREE_KIND_VHDL_ST_GENFOR,
    GW_TREE_KIND_VHDL_ST_INSTANCE,
    GW_TREE_KIND_VHDL_ST_PACKAGE,

    /* GHW VHDL signal types (still as part of scope in GHW) */
    GW_TREE_KIND_VHDL_ST_SIGNAL,
    GW_TREE_KIND_VHDL_ST_PORTIN,
    GW_TREE_KIND_VHDL_ST_PORTOUT,
    GW_TREE_KIND_VHDL_ST_PORTINOUT,
    GW_TREE_KIND_VHDL_ST_BUFFER,
    GW_TREE_KIND_VHDL_ST_LINKAGE,

    /* FSDB VHDL scope types: FSDB also reuses/defines GHW's GW_TREE_KIND_VHDL_ST_BLOCK,
       GW_TREE_KIND_VHDL_ST_GENFOR, GW_TREE_KIND_VHDL_ST_GENIF */
    /* FST reuses GW_TREE_KIND_VHDL_ST_PACKAGE */
    GW_TREE_KIND_VHDL_ST_ARCHITECTURE,
    GW_TREE_KIND_VHDL_ST_FUNCTION,
    GW_TREE_KIND_VHDL_ST_PROCEDURE,
    GW_TREE_KIND_VHDL_ST_RECORD,
    GW_TREE_KIND_VHDL_ST_PROCESS,
    GW_TREE_KIND_VHDL_ST_GENERATE
} GwTreeKind;

#ifdef WAVE_USE_STRUCT_PACKING
#pragma pack(push)
#pragma pack(1)
#endif

struct _GwTreeNode
{
    GwTreeNode *next;
    GwTreeNode *child;
    int t_which; /* 'i' for facs[i] table, value of < 0 means not a full signame */
    guint32 t_stem; /* source stem (if >0) for Open Hierarchy Source Def,  see stem_struct_t */
    guint32 t_istem; /* source stem (if >0) for Open Hierarchy Source Inst, see stem_struct_t */

    unsigned kind : 7; /* Kind of the leaf: libghw reads this as val & 0x7f so only 7 bits needed */
    unsigned children_in_gui : 1; /* indicates that the child nodes are in the gtk2 tree, but gets
                                     borrowed during tree creation for fast judy sort */
    char name[]; /* C99 */
};

#ifdef WAVE_USE_STRUCT_PACKING
#pragma pack(pop)
#endif

GwTreeNode *gw_tree_node_new(GwTreeKind kind, const gchar *name);
const gchar *gw_tree_node_get_name(GwTreeNode *self);
void gw_tree_node_free(GwTreeNode *self);

#define GW_TYPE_TREE (gw_tree_get_type())
G_DECLARE_FINAL_TYPE(GwTree, gw_tree, GW, TREE, GObject)

GwTree *gw_tree_new(GwTreeNode *root);

GwTreeNode *gw_tree_get_root(GwTree *self);
const GwTreeNode *gw_tree_get_root_const(GwTree *self);

void gw_tree_sort(GwTree *self);
void gw_tree_graft(GwTree *self, GwTreeNode *graft_chain);

G_END_DECLS