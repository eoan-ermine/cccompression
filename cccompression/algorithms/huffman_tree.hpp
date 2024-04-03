#pragma once

#include <queue>
#include <memory>
#include <vector>

#include "frequency_table.hpp"

namespace eoanermine::cccompression {

using prefix_code_table = std::unordered_map<char, std::string>;

struct huff_tree {
	char element;
	int weight;
	std::unique_ptr<huff_tree> left;
	std::unique_ptr<huff_tree> right;

	bool operator<(const huff_tree& rhs) {
		return !(weight < rhs.weight);
	}

	static std::unique_ptr<huff_tree> create(const frequency_table& table) {
		std::priority_queue<std::unique_ptr<huff_tree>, std::vector<std::unique_ptr<huff_tree>>> queue;
		for (const auto& [k, v]: table) {
			queue.push(std::make_unique<huff_tree>(k, v, nullptr, nullptr));
		}
		while (queue.size() > 1) {
			auto left = std::move(const_cast<std::unique_ptr<huff_tree>&>(queue.top()));
			queue.pop();

			auto right = std::move(const_cast<std::unique_ptr<huff_tree>&>(queue.top()));
			queue.pop();

			queue.push(std::make_unique<huff_tree>('\0', left->weight + right->weight, std::move(left), std::move(right)));
		}

		return std::move(const_cast<std::unique_ptr<huff_tree>&>(queue.top()));
	}

	prefix_code_table table() const {
		prefix_code_table res;
		encode(this, "", res);
		return res;
	}
private:
	void encode(const huff_tree* root, std::string str, prefix_code_table& res) const {
		if (!root->left && !root->right) {
			res[root->element] = str;
			return;
		}

		encode(root->left.get(), str + "0", res);
		encode(root->right.get(), str + "1", res);
	}
};

}