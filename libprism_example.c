#include <stdio.h>
#include <prism.h>

/// ruby-lang.org Example 3
const uint8_t RUBY_SOURCE[] =
  "# The Greeter class\n"
  "class Greeter\n"
  "  def initialize(name)\n"
  "    @name = name.capitalize\n"
  "  end\n"
  "\n"
  "  def salute\n"
  "    puts \"Hello #{@name}!\"\n"
  "  end\n"
  "end\n"
  "\n"
  "# Create a new object\n"
  "g = Greeter.new(\"world\")\n"
  "\n"
  "# Output \"Hello World!\"\n"
  "g.salute\n"
;

/// We have pm_prettyprint() at home.
bool print_node(const pm_node_t* node, void*) {
  printf("%"PRIu32": %s\t%.*s\n",
    node->node_id,
    pm_node_type_to_str(node->type),
    (int)(node->location.end - node->location.start),
    node->location.start
  );
  return true;
}

int main(void) {
  pm_parser_t prism;
  pm_parser_init(&prism, RUBY_SOURCE, sizeof(RUBY_SOURCE), NULL);
    pm_node_t* root = pm_parse(&prism);
      pm_visit_node(root, print_node, NULL);
    pm_node_destroy(&prism, root);
  pm_parser_free(&prism);
  return false;
}
