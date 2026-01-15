<template>
  <div
    class="h-[684px]"
    style="
      background: linear-gradient(-90deg, rgba(81, 104, 124, 0.0), rgba(56, 73, 111, 0.0)),
                 url('/cat-food-bg.jpg') center/cover no-repeat fixed;
      padding-top: 0px;
    "
  >
    <section class="max-w-4xl mx-auto px-6 pt-0 pb-4 text-center font-sans">
      <h1 class="text-6xl font-extrabold text-gray-800">
        Feed Your Lovely Pets !
      </h1>
      <h2
        class="text-xl font-semibold text-gray-700 mb-10"
        style="padding-bottom: 10px;"
      >
        🐱 Control & Scheduling 🐶
      </h2>

      <!-- Send Meal -->
      <div class="flex justify-center items-center gap-4">
        <span v-if="showEmojis" class="emoji-fade-bounce text-2xl">🐾</span>
        <button
          class="bg-[rgb(13,58,81)] hover:bg-[rgb(83,126,149)] text-white font-bold py-2 px-4 rounded shadow flex items-center"
          @click="sendMeal"
        >
          Send Meal
        </button>
        <span v-if="showEmojis" class="emoji-fade-bounce text-2xl">🐾</span>
      </div>

      <!-- Popup space -->
      <div class="h-10 flex justify-center items-center">
        <p v-if="showDefaultMessage" class="popup-fade font-semibold text-gray-600">
          Ensure your pet is fed responsibly and thoughtfully.
        </p>
        <p
          v-if="status"
          class="popup-fade font-semibold"
          :class="status.includes('❌') ? 'text-red-600' : 'text-gray-700'"
        >
          {{ status }}
        </p>
      </div>

      <!-- Schedule -->
      <div class="bg-white border border-gray-300 rounded-lg shadow p-6 max-w-md mx-auto mb-4">
        <h3 class="text-lg font-semibold text-gray-800 mb-4">
          Set Day Schedule
        </h3>
        <input
          type="time"
          id="dayTime"
          name="dayTime"
          :value="`${dayHour.padStart(2,'0')}:${dayMinute.padStart(2,'0')}`"
          @change="updateDayTime($event)"
          class="custom-time-input mb-6"
        />

        <h3 class="text-lg font-semibold text-gray-800 mb-4">
          Set Night Schedule
        </h3>
        <div class="flex flex-col items-center gap-4">
          <input
            type="time"
            id="nightTime"
            name="nightTime"
            :value="`${nightHour.padStart(2,'0')}:${nightMinute.padStart(2,'0')}`"
            @change="updateNightTime($event)"
            class="custom-time-input"
          />

          <div class="flex justify-center items-center gap-4">
            <span v-if="showClock" class="emoji-fade-bounce text-2xl">⏰</span>
            <button
              class="bg-[rgb(13,58,81)] hover:bg-[rgb(83,126,149)] text-white font-bold py-2 px-4 rounded shadow flex items-center"
              @click="setSchedule"
            >
              Save Schedule
            </button>
            <span v-if="showClock" class="emoji-fade-bounce text-2xl">⏰</span>
          </div>
        </div>
      </div>

      <!-- Saved times -->
      <div
        v-if="savedDay || savedNight"
        class="bg-white border border-gray-300 rounded-lg shadow p-6 max-w-md mx-auto mb-2"
      >
        <h3 class="text-lg font-semibold text-gray-800 mb-4">
          📅 Current Schedule 📅
        </h3>
        <p v-if="savedDay" class="text-gray-700">
          Day Schedule: {{ formatTo12Hour(savedDay) }}
        </p>
        <p v-if="savedNight" class="text-gray-700">
          Night Schedule: {{ formatTo12Hour(savedNight) }}
        </p>
      </div>
    </section>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'

const status = ref('')
const dayHour = ref('')
const dayMinute = ref('')
const nightHour = ref('')
const nightMinute = ref('')
const savedDay = ref(null)
const savedNight = ref(null)

const showEmojis = ref(false)
const showClock = ref(false)
const showDefaultMessage = ref(true)

const ESP_IP = 'http://10.58.198.63'

const showStatus = (message) => {
  const cleanMessage = message.replace(/Manual/gi, '').replace(/\(\)/g, '').trim()
  showDefaultMessage.value = false
  status.value = cleanMessage

  setTimeout(() => {
    status.value = ''
    showDefaultMessage.value = true
  }, 5000)
}

const formatTo12Hour = (time) => {
  const [hourStr, minuteStr] = time.split(':')
  let hour = parseInt(hourStr, 10)
  const minute = minuteStr.padStart(2, '0')
  const ampm = hour >= 12 ? 'PM' : 'AM'
  hour = hour % 12 || 12
  return `${hour.toString().padStart(2, '0')}:${minute} ${ampm}`
}

const sendMeal = async () => {
  try {
    const res = await fetch(`${ESP_IP}/servo/feed`)
    if (!res.ok) throw new Error('Bad response')
    const text = await res.text()
    showStatus(text)

    const audio = new Audio('/hector-bell.mp3')
    audio.play().catch(err => console.error('Audio play failed:', err))

    showEmojis.value = true
    setTimeout(() => (showEmojis.value = false), 5000)
  } catch (err) {
    showStatus('❌ Error: Could not reach ESP8266')
  }
}

const setSchedule = async () => {
  try {
    const res = await fetch(
      `${ESP_IP}/setSchedule?dayHour=${dayHour.value}&dayMinute=${dayMinute.value}&nightHour=${nightHour.value}&nightMinute=${nightMinute.value}`
    )
    if (!res.ok) throw new Error('Bad response')
    const text = await res.text()
    showStatus(text)

    savedDay.value = `${dayHour.value.padStart(2, '0')}:${dayMinute.value.padStart(2, '0')}`
    savedNight.value = `${nightHour.value.padStart(2, '0')}:${nightMinute.value.padStart(2, '0')}`

    showClock.value = true
    setTimeout(() => (showClock.value = false), 5000)
  } catch (err) {
    showStatus('❌ Error: Could not reach ESP8266')
  }
}

const updateDayTime = (e) => {
  const [hour, minute] = e.target.value.split(':')
  dayHour.value = hour
  dayMinute.value = minute
}

const updateNightTime = (e) => {
  const [hour, minute] = e.target.value.split(':')
  nightHour.value = hour
  nightMinute.value = minute
}

onMounted(async () => {
  try {
    const res = await fetch(`${ESP_IP}/getSchedule`)
    if (!res.ok) throw new Error('Bad response')
    const data = await res.json()

    dayHour.value = String(data.dayHour)
    dayMinute.value = String(data.dayMinute)
    nightHour.value = String(data.nightHour)
    nightMinute.value = String(data.nightMinute)

    savedDay.value = `${String(data.dayHour).padStart(2, '0')}:${String(data.dayMinute).padStart(2, '0')}`
    savedNight.value = `${String(data.nightHour).padStart(2, '0')}:${String(data.nightMinute).padStart(2, '0')}`
  } catch (err) {
    console.error(err)
    showStatus('❌ Error: Could not fetch schedule from ESP8266')
  }
})
</script>

<style scoped>
/* Scoped styles if needed, otherwise rely on Tailwind/App.css */
</style>
