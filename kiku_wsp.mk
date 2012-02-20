.PHONY: clean All

All:
	@echo ----------Building project:[ kiku - Debug ]----------
	@cd "kiku" && "$(MAKE)" -f "kiku.mk"
clean:
	@echo ----------Cleaning project:[ kiku - Debug ]----------
	@cd "kiku" && "$(MAKE)" -f "kiku.mk" clean
