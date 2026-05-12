#!/usr/bin/env bash
# Claude Code status line script
# Shows: git branch | context usage | 5h session usage | 7d weekly usage

input=$(cat)

# --- Git branch ---
git_branch=$(git --git-dir="$(echo "$input" | jq -r '.workspace.project_dir // empty')/.git" \
    --work-tree="$(echo "$input" | jq -r '.workspace.project_dir // empty')" \
    symbolic-ref --short HEAD 2>/dev/null || \
  git -C "$(echo "$input" | jq -r '.workspace.current_dir // empty')" \
    symbolic-ref --short HEAD 2>/dev/null)

# --- Context window ---
used_pct=$(echo "$input" | jq -r '.context_window.used_percentage // empty')

# --- Rate limits (Pro plan: 5-hour session / 7-day weekly) ---
five_pct=$(echo "$input" | jq -r '.rate_limits.five_hour.used_percentage // empty')
week_pct=$(echo "$input" | jq -r '.rate_limits.seven_day.used_percentage // empty')

# --- Build output parts ---
parts=()

if [ -n "$git_branch" ]; then
  parts+=("$(printf '\033[36m\xee\x82\xa0 %s\033[0m' "$git_branch")")
fi

if [ -n "$used_pct" ]; then
  used_int=$(printf '%.0f' "$used_pct")
  if [ "$used_int" -ge 80 ]; then
    color='\033[31m'   # red
  elif [ "$used_int" -ge 50 ]; then
    color='\033[33m'   # yellow
  else
    color='\033[32m'   # green
  fi
  parts+=("$(printf "${color}ctx:%s%%\033[0m" "$used_int")")
fi

if [ -n "$five_pct" ]; then
  five_int=$(printf '%.0f' "$five_pct")
  if [ "$five_int" -ge 80 ]; then
    color='\033[31m'
  elif [ "$five_int" -ge 50 ]; then
    color='\033[33m'
  else
    color='\033[32m'
  fi
  parts+=("$(printf "${color}5h:%s%%\033[0m" "$five_int")")
fi

if [ -n "$week_pct" ]; then
  week_int=$(printf '%.0f' "$week_pct")
  if [ "$week_int" -ge 80 ]; then
    color='\033[31m'
  elif [ "$week_int" -ge 50 ]; then
    color='\033[33m'
  else
    color='\033[32m'
  fi
  parts+=("$(printf "${color}7d:%s%%\033[0m" "$week_int")")
fi

# --- Join with separator and print ---
printf '%s' "$(IFS=' | '; echo "${parts[*]}")"
