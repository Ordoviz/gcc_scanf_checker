// clang-format off
// order of #includes matters
#include <gcc-plugin.h>
#include <tree.h>
#include <plugin-version.h>
#include <gimple.h>
#include <gimple-iterator.h>
#include <diagnostic.h>
// clang-format on

#include <assert.h>

int plugin_is_GPL_compatible;

static const char *get_string_from_tree(tree tr) {
	switch (TREE_CODE(tr)) {
	case STRING_CST:
		return TREE_STRING_POINTER(tr);
	case ADDR_EXPR:
		return get_string_from_tree(TREE_OPERAND(tr, 0));
	case SSA_NAME: {
		gimple *def_stmt = SSA_NAME_DEF_STMT(tr);
		assert(def_stmt && gimple_assign_single_p(def_stmt));
		return get_string_from_tree(gimple_assign_rhs1(def_stmt));
	}
	default:
		return nullptr;
	}
}

static void plugin_callback(void *, void *) {
	basic_block bb;
	FOR_EACH_BB_FN(bb, cfun) {
		gimple_stmt_iterator gsi;
		for (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
			gimple *stmt = gsi_stmt(gsi);

			if (!is_gimple_call(stmt))
				continue;
			tree fn_decl = gimple_call_fndecl(stmt);
			if (fn_decl == NULL_TREE)
				continue;
			if (TREE_CODE(fn_decl) != FUNCTION_DECL)
				continue;

			if (!strcmp(IDENTIFIER_POINTER(DECL_NAME(fn_decl)), "scanf")) {
				const char *fmt = get_string_from_tree(gimple_call_arg(stmt, 0));
				if (fmt && strstr(fmt, "%s")) {
					warning_at(gimple_location(stmt), OPT_fplugin_,
					           "format string contains insecure %%s specifier");
				}
			}
		}
	}
}

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {
	if (!plugin_default_version_check(version, &gcc_version)) {
		return 1;
	}

	register_callback(plugin_info->base_name, PLUGIN_ALL_PASSES_START, plugin_callback, NULL);
	return 0;
}
