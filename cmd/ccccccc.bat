::cmd
::https://github.com/1424234500/help_note.git		-> E:/ help_note	
::https://github.com/1424234500/base.git			-> E:/ workspqce_my/ * 
::https://github.com/1424234500/BaseSSM.git
::https://github.com/1424234500/cc.git
::https://github.com/1424234500/GraphicsTools.git 
::批量 github 添加 提交 推送的操作


call echo -------------- my git projects add submit 

call git-add-commit-E-dir E: help_note

call git-add-commit-E-dir E: workspace_my/base 
call git-add-commit-E-dir E: workspace_my/BaseSSM
call git-add-commit-E-dir E: workspace_my/cc
call git-add-commit-E-dir E: workspace_my/GraphicsTools 


call echo ------------------------------end