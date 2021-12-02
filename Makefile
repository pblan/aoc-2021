clean: ## Clean up
	@rm -rvf build
	@rm -rvf day*/build
	
build: ## Compile all days
	cmake -H. -B build && make -j -C build

run: ## Run all days
	@cd build;\
	for day in `ls -d day*`; do \
		cd $$day && ./$$day && cd ..; \
	done

.PHONY: clean build help interact compile run
.DEFAULT_GOAL := help